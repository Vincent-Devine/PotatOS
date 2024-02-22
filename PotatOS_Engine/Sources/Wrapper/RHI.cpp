#include "pch.h"

#include <Wrapper/RHI.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <DebugSystem/Assertion.hpp>
#include <Wrapper/LoaderImage.hpp>
#include <Wrapper/FontRenderer.hpp>

namespace Wrapper
{
	RHI* RHI::singleton = nullptr;

	void CheckCompileErrors(GLuint p_shader, std::string p_type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (p_type != "PROGRAM")
		{
			glGetShaderiv(p_shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(p_shader, 1024, NULL, infoLog);
				Log::Print("ERROR::SHADER_COMPILATION_ERROR of type: " + p_type + "\n" + infoLog + "\n -- --------------------------------------------------- -- ", LOG_LEVEL_TYPE::Critical);
			}
		}
		else
		{
			glGetProgramiv(p_shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(p_shader, 1024, NULL, infoLog);
				Log::Print("ERROR::PROGRAM_LINKING_ERROR of type: " + p_type + "\n" + infoLog + "\n -- --------------------------------------------------- -- ", LOG_LEVEL_TYPE::Critical);
			}
		}
	}


	void RHI::Init(const unsigned int p_width, const unsigned int p_height)
	{
		width = p_width;
		height = p_height;

		//colorModificationMatrix = Math::Mat4::Identity();
		colorModificationMatrix = ColorVisionDeficiency::ColorMatrix(ColorVisionDeficiency::VISION_TYPE::NORMAL);

		Assertion(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD.");

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		CreateFrameBuffer(p_width, p_height);

		hdrShader = new Resource::Shader(0, "Resources/Shaders/PostProcess.vert", "Resources/Shaders/PostProcess.frag");
		hdrShader->Init();
		hdrShader->InitRHI();
		
		hdrShader->Use();
		hdrShader->SetInt("scene", 0);
		hdrShader->SetInt("bloomBuffer", 1);

		CreateQuad();

		// Exposure
		exposure = .5f;

		// Blur
		blurShader = new Resource::Shader(0, "Resources/Shaders/PostProcess.vert", "Resources/Shaders/Blur.frag");
		blurShader->Init();
		blurShader->InitRHI();

		blurShader->Use();
		blurShader->SetInt("blurBuffer", 0);

		// bloom
		bloomIsActive = true;

		// Game
		gameShader = new Resource::Shader(0, "Resources/Shaders/Game.vert", "Resources/Shaders/Game.frag");
		gameShader->Init();
		gameShader->InitRHI();
		gameShader->SetInt("texture_", 0);
	}

	void RHI::RenderShadow(Core::Scene* p_scene)
	{
		DataStructure::LightManager lightManager = p_scene->GetLightManager();
		for (unsigned int i = 0U; i < lightManager.GetDirectionalLightSize(); ++i)
		{
			lightManager.DrawDirectionalShadow(i);
			p_scene->DrawFromLightPosition(lightManager.GetDirectionalLightAsLight(i));
		}
		for (unsigned int i = 0U; i < lightManager.GetSpotLightSize(); ++i)
		{
			lightManager.DrawSpotShadow(i);
			p_scene->DrawFromLightPosition(lightManager.GetSpotLightAsLight(i));
		}
	}

	void RHI::Render(Core::Scene* p_scene)
	{
		RenderShadow(p_scene);
		// reset viewport
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glClearColor(0.05f, 0.05f, 0.05f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);

		p_scene->Draw();

		bool horizontal = true;
		bool firstIteration = true;
		unsigned int amount = 10; // Need to be even
		blurShader->Use();
		for (unsigned int i = 0; i < amount; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
			blurShader->SetBool("horizontal", horizontal);

			if (firstIteration)
			{
				glBindTexture(GL_TEXTURE_2D, bloomBuffer);
				firstIteration = false;
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, pingpongBuffer[!horizontal]);
			}

			RenderQuad();
			horizontal = !horizontal;
		}

		hdrShader->Use();
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, postProcessTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, pingpongBuffer[!horizontal]);

		hdrShader->SetFloat("exposure", exposure);
		hdrShader->SetBool("bloom", bloomIsActive);

		RenderQuad();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RHI::Destroy()
	{
		delete hdrShader;
		delete blurShader;
		delete gameShader;
	}

	void RHI::DisplayTexture(const unsigned int p_texture)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.05f, 0.05f, 0.05f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gameShader->Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, p_texture);
		RenderQuad();
	}

	RHI* RHI::Get()
	{
		if (singleton == nullptr)
		{
			singleton = new RHI;
		}
		return singleton;
	}

	void RHI::UnbindFrameBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RHI::InitTexture(unsigned int& p_idTexture, unsigned char* p_data, const int p_width, const int p_height, const int p_channels, const std::string& p_path)
	{
		glGenTextures(1, &p_idTexture);

		GLenum internalFormat = GL_RGB;
		GLenum dataFormat = GL_RGB;
		if (p_channels == 1)
		{
			internalFormat = dataFormat = GL_RED;
		}
		else if (p_channels == 3)
		{
			internalFormat = GL_SRGB;
			dataFormat = GL_RGB;
		}
		else if (p_channels == 4)
		{
			internalFormat = GL_SRGB_ALPHA;
			dataFormat = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, p_idTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, p_width, p_height, 0, dataFormat, GL_UNSIGNED_BYTE, p_data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void RHI::DrawTexture(const unsigned int p_idTexture, const unsigned int p_shaderProgram)
	{
		SetIntShader(p_shaderProgram, "texture_", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, p_idTexture);
	}

	void RHI::BindShadowTexture(const unsigned int p_textureID, const unsigned int p_location)
	{
		glActiveTexture(GL_TEXTURE0 + p_location);
		glBindTexture(GL_TEXTURE_2D, p_textureID);
		glActiveTexture(GL_TEXTURE0);
	}

	void RHI::ColorVisionDeficiencyFilter(const unsigned int p_shaderProgram)
	{
		colorModificationMatrix = ColorVisionDeficiency::ColorMatrix(visionType);
		SetBoolShader(p_shaderProgram, "isColorDifference", seeColorDifference);
		SetVec3Shader(p_shaderProgram, "colorDifferenceHighlight", colorDifferenceHighlight);
		SetMat4Shader(p_shaderProgram, "colorModificationMatrix", colorModificationMatrix);
	}

	void RHI::DestroyTexture(unsigned int& p_idTexture, unsigned int& p_sampler)
	{
		glDeleteTextures(1, &p_idTexture);
		glDeleteSamplers(1, &p_sampler);
	}

	void RHI::InitMesh(unsigned int& p_VBO, unsigned int& p_VAO, unsigned int& p_EBO, const std::vector<Vertex>& p_vertexBuffer, const std::vector<unsigned int>& p_indexBuffer, const std::string& p_name)
	{
		glGenBuffers(1, &p_VBO);
		glGenBuffers(1, &p_EBO);
		glGenVertexArrays(1, &p_VAO);

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(p_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
		glBufferData(GL_ARRAY_BUFFER, p_vertexBuffer.size() * sizeof(Vertex), p_vertexBuffer.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_indexBuffer.size() * sizeof(unsigned int), p_indexBuffer.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Math::Vector3)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(Math::Vector3)));
		glEnableVertexAttribArray(2);
		// ids bone
		glVertexAttribIPointer(3, 4, GL_INT, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::boneIDs)));
		glEnableVertexAttribArray(3);
		// bone weights
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::weights)));
		glEnableVertexAttribArray(4);

		Log::Print("Load Mesh (" + p_name + ")!", LOG_LEVEL_TYPE::Notification);
	}

	void RHI::DrawMesh(const unsigned int p_VAO, const std::vector<unsigned int>& p_indexBuffer)
	{
		glBindVertexArray(p_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(p_indexBuffer.size()), GL_UNSIGNED_INT, 0);
	}

	void RHI::DestroyMesh(unsigned int& p_VBO, unsigned int& p_VAO, unsigned int& p_EBO)
	{
		if (p_VAO != 0)
		{
			glDeleteVertexArrays(1, &p_VAO);
		}
		if (p_VBO != 0)
		{
			glDeleteBuffers(1, &p_VBO);
		}
		if (p_EBO != 0)
		{
			glDeleteBuffers(1, &p_EBO);
		}
	}

	void RHI::InitCollider(unsigned int& p_VBO, unsigned int& p_VAO, unsigned int& p_EBO, const std::vector<Math::Vector3>& p_vertexBuffer, const std::vector<unsigned int>& p_indexBuffer, const std::string& p_name)
	{
		glGenBuffers(1, &p_VBO);
		glGenBuffers(1, &p_EBO);
		glGenVertexArrays(1, &p_VAO);

		glBindVertexArray(p_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
		glBufferData(GL_ARRAY_BUFFER, p_vertexBuffer.size() * sizeof(Math::Vector3), p_vertexBuffer.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_indexBuffer.size() * sizeof(unsigned int), p_indexBuffer.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Math::Vector3), (void*)0);
		glEnableVertexAttribArray(0);

		Log::Print("Load Collider (" + p_name + ")!", LOG_LEVEL_TYPE::Notification);
	}

	void RHI::DrawCollider(const unsigned int p_VAO, const unsigned int p_indexBufferSize)
	{
		glBindVertexArray(p_VAO);
		glDrawElements(GL_LINES, static_cast<GLsizei>(p_indexBufferSize), GL_UNSIGNED_INT, 0);
	}

	void RHI::RebindCollider(const unsigned int p_VBO, const unsigned int p_VAO, const unsigned int p_EBO, const std::vector<Math::Vector3>& p_vertexBuffer, const std::vector<unsigned int>& p_indexBuffer)
	{
		glBindVertexArray(p_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
		glBufferData(GL_ARRAY_BUFFER, p_vertexBuffer.size() * sizeof(Math::Vector3), p_vertexBuffer.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_indexBuffer.size() * sizeof(unsigned int), p_indexBuffer.data(), GL_STATIC_DRAW);
	}

	void RHI::InitDepthMap(unsigned int* p_depthMapFBO, unsigned int* p_depthMap, unsigned int p_shadowSize)
	{
		glGenFramebuffers(1, p_depthMapFBO);
		// create depth texture
		glGenTextures(1, p_depthMap);
		glBindTexture(GL_TEXTURE_2D, *p_depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, p_shadowSize, p_shadowSize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
		// attach depth texture as FBO's depth buffer
		glBindFramebuffer(GL_FRAMEBUFFER, *p_depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *p_depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RHI::BindDepthMap(unsigned int p_shadowSize, unsigned int p_depthMapFBO, unsigned int p_depthMap)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, p_depthMapFBO);
		glViewport(0, 0, p_shadowSize, p_shadowSize);
		glClear(GL_DEPTH_BUFFER_BIT);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, p_depthMap, 0);
	}

	void RHI::InitCanva(unsigned int& p_VBO, unsigned int& p_VAO)
	{
		glGenVertexArrays(1, &p_VAO);
		glGenBuffers(1, &p_VBO);
		glBindVertexArray(p_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	void RHI::StartCanva(const unsigned int p_VAO)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindVertexArray(p_VAO);
		glActiveTexture(GL_TEXTURE0);
	}

	void RHI::DrawCanva(const unsigned int p_VAO, const unsigned int p_VBO, const unsigned int p_charTextID, const float (& vertices)[6][4])
	{
		glBindTexture(GL_TEXTURE_2D, p_charTextID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void RHI::BindCanva()
	{
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}

	const char* GetGLErrorString(GLenum error)
	{
		switch (error)
		{
		case GL_NO_ERROR:
			return "No error";
		case GL_INVALID_ENUM:
			return "Invalid enum";
		case GL_INVALID_VALUE:
			return "Invalid value";
		case GL_INVALID_OPERATION:
			return "Invalid operation";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return "Invalid framebuffer operation";
		case GL_OUT_OF_MEMORY:
			return "Out of memory";
		default:
			return "Unknown error";
		}

		/*GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			const char* errorMessage = GetGLErrorString(error);
			printf("OpenGL error: %s\n", errorMessage);
		}*/
	}

	void RHI::InitSoundAsset(unsigned int p_VBO, unsigned int p_VAO, unsigned int p_charTextID, const float(&vertices)[4][2])
	{
		glGenVertexArrays(1, &p_VAO);
		glBindVertexArray(p_VAO);

		// Create and bind the VBO
		glGenBuffers(1, &p_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Define the vertex attributes
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Unbind the VAO and VBO
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Enable alpha blending for transparency
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RHI::DrawSoundAsset(const unsigned int p_VAO, const unsigned int p_VBO, const unsigned int p_charTextID, const float(&vertices)[6][4])
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

			glBindTexture(GL_TEXTURE_2D, p_charTextID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void RHI::BindSoundAsset(unsigned int p_VAO, unsigned int p_charTextID)
	{
		glBindVertexArray(p_VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindVertexArray(0);
	}

	void RHI::InitShader(const std::string& p_vertexPath, const std::string& p_fragmentPath, unsigned int& p_shaderProgram)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(p_vertexPath);
			fShaderFile.open(p_fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT");
		// shader Program
		p_shaderProgram = glCreateProgram();
		glAttachShader(p_shaderProgram, vertex);
		glAttachShader(p_shaderProgram, fragment);
		glLinkProgram(p_shaderProgram);
		CheckCompileErrors(p_shaderProgram, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	void RHI::UseShader(const unsigned int p_shaderProgram)
	{
		glUseProgram(p_shaderProgram);
	}

	void RHI::SetBoolShader(const unsigned int p_shaderProgram, const std::string& p_name, bool p_value)
	{
		glUniform1i(glGetUniformLocation(p_shaderProgram, p_name.c_str()), (int)p_value);
	}

	void RHI::SetIntShader(const unsigned int p_shaderProgram, const std::string& p_name, int p_value)
	{
		glUniform1i(glGetUniformLocation(p_shaderProgram, p_name.c_str()), p_value);
	}

	void RHI::SetFloatShader(const unsigned int p_shaderProgram, const std::string& p_name, float p_value)
	{
		glUniform1f(glGetUniformLocation(p_shaderProgram, p_name.c_str()), p_value);
	}

	void RHI::SetVec2Shader(const unsigned int p_shaderProgram, const std::string& p_name, const Math::Vector2& p_value)
	{
		glUniform2fv(glGetUniformLocation(p_shaderProgram, p_name.c_str()), 1, &p_value.x);
	}

	void RHI::SetVec2Shader(const unsigned int p_shaderProgram, const std::string& p_name, float p_x, float p_y)
	{
		glUniform2f(glGetUniformLocation(p_shaderProgram, p_name.c_str()), p_x, p_y);
	}

	void RHI::SetVec3Shader(const unsigned int p_shaderProgram, const std::string& p_name, const Math::Vector3& p_value)
	{
		glUniform3fv(glGetUniformLocation(p_shaderProgram, p_name.c_str()), 1, &p_value.x);
	}

	void RHI::SetVec3Shader(const unsigned int p_shaderProgram, const std::string& p_name, float p_x, float p_y, float p_z)
	{
		glUniform3f(glGetUniformLocation(p_shaderProgram, p_name.c_str()), p_x, p_y, p_z);
	}

	void RHI::SetVec4Shader(const unsigned int p_shaderProgram, const std::string& p_name, const Math::Vector4& p_value)
	{
		glUniform4fv(glGetUniformLocation(p_shaderProgram, p_name.c_str()), 1, &p_value.x);
	}

	void RHI::SetVec4Shader(const unsigned int p_shaderProgram, const std::string& p_name, float p_x, float p_y, float p_z, float p_w)
	{
		glUniform4f(glGetUniformLocation(p_shaderProgram, p_name.c_str()), p_x, p_y, p_z, p_w);
	}

	void RHI::SetMat4Shader(const unsigned int p_shaderProgram, const std::string& p_name, const Math::Mat4& p_mat)
	{
		glUniformMatrix4fv(glGetUniformLocation(p_shaderProgram, p_name.c_str()), 1, GL_TRUE, &p_mat.data[0][0]);
	}

	void RHI::CreateFrameBuffer(const unsigned int p_width, const unsigned int p_height)
	{
		glGenFramebuffers(1, &FBO);

		// create floating point color buffer
		glGenTextures(1, &postProcessTexture);
		glBindTexture(GL_TEXTURE_2D, postProcessTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, p_width, p_height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// create second floating point color buffer for bloom
		glGenTextures(1, &bloomBuffer);
		glBindTexture(GL_TEXTURE_2D, bloomBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, p_width, p_height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		// create depth buffer (renderbuffer)
		unsigned int depthBuffer;
		glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, p_width, p_height);
		
		// attach buffers
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, postProcessTexture, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, bloomBuffer, 0);
		unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, attachments);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
		
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			Log::Print("Framebuffer not complete.", LOG_LEVEL_TYPE::Critical);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		// Pingpong buffer
		glGenFramebuffers(2, pingpongFBO);
		glGenTextures(2, pingpongBuffer);
		for (unsigned int i = 0; i < 2; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
			glBindTexture(GL_TEXTURE_2D, pingpongBuffer[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, p_width, p_height, 0, GL_RGBA, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongBuffer[i], 0);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				Log::Print("Ping-Pong Framebuffer error.", LOG_LEVEL_TYPE::Critical);
			}
		}
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void RHI::CreateQuad()
	{
		// Mesh
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};

		// setup plane VAO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}

	void RHI::RenderQuad()
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}
}
