#pragma once

#include <DLLInclude.hpp>

#include <Resource/IResource.hpp>
#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Mat4.inl>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/Shader.rfkh.h>

namespace Resource RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API Shader : public IResource
	{
	// Attributes
	private:
		std::string vertexPath;

		std::string fragmentPath;
		unsigned int shaderProgram;

	// Methods
	public:
		Shader(const unsigned int p_id, const std::string& p_vertexPath, const std::string& p_fragmentPath);
		Shader(const Shader& p_shader);
		
		const bool InitRHI() override;

		void Use();

		void SetBool(const std::string& p_name, bool p_value);
		void SetInt(const std::string& p_name, int p_value);
		void SetFloat(const std::string& p_name, float p_value);
		void SetVec2(const std::string& p_name, const Math::Vector2& p_value);
		void SetVec2(const std::string& p_name, float p_x, float p_y);
		void SetVec3(const std::string& p_name, const Math::Vector3& p_value);
		void SetVec3(const std::string& p_name, float p_x, float p_y, float p_z);
		void SetVec4(const std::string& p_name, const Math::Vector4& p_value);
		void SetVec4(const std::string& p_name, float p_x, float p_y, float p_z, float p_w);
		void SetMat4(const std::string& p_name, const Math::Mat4& p_mat);

		const unsigned int* GetShaderProgram() const { return &shaderProgram; };
		const std::string& GetVertexPath() const { return vertexPath; };
		const std::string& GetFragmentPath() const { return fragmentPath; };

		Resource_Shader_GENERATED
	};
}
File_Shader_GENERATED
