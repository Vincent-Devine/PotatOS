#include "pch.h"

#include <Resource/Shader.hpp>

#include <Wrapper/RHI.hpp>

namespace Resource
{
	Shader::Shader(const unsigned int p_id, const std::string& p_vertexPath, const std::string& p_fragmentPath)
	{
		usedBy = 0;
		vertexPath = p_vertexPath;
		fragmentPath = p_fragmentPath;
		path = p_vertexPath;
		id = p_id;
		CreateName();
	}

	Shader::Shader(const Shader& p_shader)
	{
		usedBy = 0;
		vertexPath = p_shader.vertexPath;
		fragmentPath = p_shader.fragmentPath;
		path = p_shader.vertexPath;
		id = p_shader.id;
		name = p_shader.name;
		shaderProgram = p_shader.shaderProgram;
	}

	const bool Shader::InitRHI()
	{
		Wrapper::RHI::InitShader(vertexPath, fragmentPath, shaderProgram);
		isFinishToInit = true;
		return true;
	}

	void Shader::Use()
	{
		Wrapper::RHI::UseShader(shaderProgram);
	}

	void Shader::SetBool(const std::string& p_name, bool p_value)
	{
		Wrapper::RHI::SetBoolShader(shaderProgram, p_name, p_value);
	}

	void Shader::SetInt(const std::string& p_name, int p_value)
	{
		Wrapper::RHI::SetIntShader(shaderProgram, p_name, p_value);
	}

	void Shader::SetFloat(const std::string& p_name, float p_value)
	{
		Wrapper::RHI::SetFloatShader(shaderProgram, p_name, p_value);
	}

	void Shader::SetVec2(const std::string& p_name, const Math::Vector2& p_value)
	{
		Wrapper::RHI::SetVec2Shader(shaderProgram, p_name, p_value);
	}

	void Shader::SetVec2(const std::string& p_name, float p_x, float p_y)
	{
		Wrapper::RHI::SetVec2Shader(shaderProgram, p_name, p_x, p_y);
	}

	void Shader::SetVec3(const std::string& p_name, const Math::Vector3& p_value)
	{
		Wrapper::RHI::SetVec3Shader(shaderProgram, p_name, p_value);
	}

	void Shader::SetVec3(const std::string& p_name, float p_x, float p_y, float p_z)
	{
		Wrapper::RHI::SetVec3Shader(shaderProgram, p_name, p_x, p_y, p_z);
	}

	void Shader::SetVec4(const std::string& p_name, const Math::Vector4& p_value)
	{
		Wrapper::RHI::SetVec4Shader(shaderProgram, p_name, p_value);
	}

	void Shader::SetVec4(const std::string& p_name, float p_x, float p_y, float p_z, float p_w)
	{
		Wrapper::RHI::SetVec4Shader(shaderProgram, p_name, p_x, p_y, p_z, p_w);
	}

	void Shader::SetMat4(const std::string& p_name, const Math::Mat4& p_mat)
	{
		Wrapper::RHI::SetMat4Shader(shaderProgram, p_name, p_mat);
	}
}
