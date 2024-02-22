#pragma once
#include <DLLInclude.hpp>

#include <string>
#include <vector>

#include <Common.hpp>
#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Mat4.inl>

#include <Core/Scene.hpp>
#include <Resource/Shader.hpp>

#include <ColorBlind.hpp>

namespace Wrapper
{
	class POTATOS_ENGINE_API RHI
	{
		// Attribute
	public:
		// HDR
		float exposure;

	private:

		static RHI* singleton;

		unsigned int width;
		unsigned int height;

		// Frame Buffer Object
		unsigned int postProcessTexture;
		unsigned int bloomBuffer; // Bloom texture

		// HDR
		Resource::Shader* hdrShader;
		unsigned int VAO, VBO; // Mesh

		// Bloom
		Resource::Shader* blurShader;
		unsigned int pingpongBuffer[2];
		bool bloomIsActive;

		// ColorBlind friendly development
		ColorVisionDeficiency::VISION_TYPE visionType = ColorVisionDeficiency::VISION_TYPE::NORMAL;
		Math::Mat4 colorModificationMatrix;
		bool seeColorDifference = false;
		Math::Vector3 colorDifferenceHighlight = Math::Vector3(1.f, 1.f, 0.f);

		// Game
		Resource::Shader* gameShader;

		// Sound Asset
		unsigned int soundAssetText; 

		// Methods
	public:
		unsigned int pingpongFBO[2];
		unsigned int FBO;
		void Init(const unsigned int p_width, const unsigned int p_height);
		void RenderShadow(Core::Scene* p_scene);
		void Render(Core::Scene* p_scene);
		void Destroy();

		void DisplayTexture(const unsigned int p_texture);

		static RHI* Get();

		unsigned int GetTextureToRender() { return pingpongBuffer[0]; };

		static void UnbindFrameBuffer();

		// Texture
		static void InitTexture(unsigned int& p_idTexture, unsigned char* p_data, const int p_width, const int p_height, const int p_channels, const std::string& p_path);
		static void DrawTexture(const unsigned int p_idTexture, const unsigned int p_shaderProgram);
		static void DestroyTexture(unsigned int& p_idTexture, unsigned int& p_sampler);

		// Mesh
		static void InitMesh(unsigned int& p_VBO, unsigned int& p_VAO, unsigned int& p_EBO, const std::vector<Vertex>& p_vertexBuffer, const std::vector<unsigned int>& p_indexBuffer, const std::string& p_name);
		static void DrawMesh(const unsigned int p_VAO, const std::vector<unsigned int>& p_indexBuffer);
		static void DestroyMesh(unsigned int& p_VBO, unsigned int& p_VAO, unsigned int& p_EBO);

		// Collider
		static void InitCollider(unsigned int& p_VBO, unsigned int& p_VAO, unsigned int& p_EBO, const std::vector<Math::Vector3>& p_vertexBuffer, const std::vector<unsigned int>& p_indexBuffer, const std::string& p_name);
		static void DrawCollider(const unsigned int p_VAO, const unsigned int p_indexBufferSize);
		static void RebindCollider(const unsigned int p_VBO, const unsigned int p_VAO, const unsigned int p_EBO, const std::vector<Math::Vector3>& p_vertexBuffer, const std::vector<unsigned int>& p_indexBuffer);

		// Shadows
		static void InitDepthMap(unsigned int* p_depthMapFBO, unsigned int* p_depthMap, unsigned int p_shadowSize);
		static void BindDepthMap(unsigned int p_shadowSize, unsigned int p_depthMapFBO, unsigned int p_depthMap);
		static void BindShadowTexture(const unsigned int p_textureID, const unsigned int p_location);

		// Color Vision Deficiency
		void ColorVisionDeficiencyFilter(const unsigned int p_shaderProgram);

		//Canva
		void InitCanva(unsigned int& p_VBO, unsigned int& p_VAO);
		void StartCanva(const unsigned int p_VAO);
		void DrawCanva(const unsigned int p_VAO, const unsigned int p_VBO, const unsigned int p_charTextID, const float(&vertices)[6][4]);
		void BindCanva();

		//Sound Dir
		void InitSoundAsset(unsigned int p_VBO, unsigned int p_VAO, unsigned int p_charTextID, const float(&vertices)[4][2]);
		void DrawSoundAsset(const unsigned int p_VAO, const unsigned int p_VBO, const unsigned int p_charTextID, const float(&vertices)[6][4]);
		void BindSoundAsset(unsigned int p_VAO, unsigned int p_charTextID);
		
		// Shader
		static void InitShader(const std::string& p_vertexPath, const std::string& p_fragmentPath, unsigned int& p_shaderProgram);
		static void UseShader(const unsigned int p_shaderProgram);
		static void SetBoolShader(const unsigned int p_shaderProgram, const std::string& p_name, bool p_value);
		static void SetIntShader(const unsigned int p_shaderProgram, const std::string& p_name, int p_value);
		static void SetFloatShader(const unsigned int p_shaderProgram, const std::string& p_name, float p_value);
		static void SetVec2Shader(const unsigned int p_shaderProgram, const std::string& p_name, const Math::Vector2& p_value);
		static void SetVec2Shader(const unsigned int p_shaderProgram, const std::string& p_name, float p_x, float p_y);
		static void SetVec3Shader(const unsigned int p_shaderProgram, const std::string& p_name, const Math::Vector3& p_value);
		static void SetVec3Shader(const unsigned int p_shaderProgram, const std::string& p_name, float p_x, float p_y, float p_z);
		static void SetVec4Shader(const unsigned int p_shaderProgram, const std::string& p_name, const Math::Vector4& p_value);
		static void SetVec4Shader(const unsigned int p_shaderProgram, const std::string& p_name, float p_x, float p_y, float p_z, float p_w);
		static void SetMat4Shader(const unsigned int p_shaderProgram, const std::string& p_name, const Math::Mat4& p_mat);
	
		ColorVisionDeficiency::VISION_TYPE* GetVisionType() { return &visionType; };
		void SetVisionType(ColorVisionDeficiency::VISION_TYPE p_visionType) { visionType = p_visionType; };

	private:
		void CreateQuad();
		void CreateFrameBuffer(const unsigned int p_width, const unsigned int p_height);
		void RenderQuad();
	};
}
