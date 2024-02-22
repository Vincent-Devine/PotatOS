#include "pch.h"

#include <MonoBehavior/Renderer/DirectionalLight.hpp>
#include <Wrapper/RHI.hpp>

namespace MonoBehavior::Renderer
{
	DirectionalLight::DirectionalLight(const InitLight& p_initLight, const Math::Vector3& p_diretion)
		: direction(p_diretion)
	{
		componentType = DIRECTIONAL_LIGHT;
		ambient = p_initLight.ambient;
		diffuse = p_initLight.diffuse;
		specular = p_initLight.specular; 
		projectionMatrix = Math::Mat4::GetOrthographicProjection(-100.0f, 100.0f, -100.0f, 100.0f, -100.f, 100.f);
	}

	void DirectionalLight::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		viewMatrix = Math::Mat4::LookAt(gameObject->transform.GetPosition(), gameObject->transform.GetPosition() + Math::Vector3(0.000001f, 0.0f, 0.000001f) + direction, Math::Vector3(0.f, 1.f, 0.f));
		Light::Update(p_deltaTime, p_inputs);
	}

	void DirectionalLight::DrawLight(const int p_shaderProgram, const Math::Vector3& p_camPosition, const unsigned int p_index) const
	{
		std::string array = "directionalLights[" + std::to_string(p_index) + "].";

		Wrapper::RHI::SetIntShader(p_shaderProgram, (array + "lightData." + "shadowMap").c_str(), id);
		Wrapper::RHI::SetVec3Shader(p_shaderProgram, (array + "direction").c_str(), direction);

		Light::DrawLight(p_shaderProgram, p_camPosition, array);
		Wrapper::RHI::SetVec3Shader(p_shaderProgram, (array + "lightData." + "lightPosition").c_str(), gameObject->transform.GetPosition() - direction);
	}
}
