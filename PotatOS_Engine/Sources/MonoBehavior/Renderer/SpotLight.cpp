#include "pch.h"

#include <MonoBehavior/Renderer/SpotLight.hpp>
#include <Wrapper/RHI.hpp>

namespace MonoBehavior::Renderer
{
	SpotLight::SpotLight(const InitLight& p_initLight, const Math::Vector3& p_direction, const float p_cutOff, const float p_outerCutOff, const float p_constant, const float p_linear, const float p_quadratic):
		direction(p_direction),
		cutOff(p_cutOff),
		outerCutOff(p_outerCutOff),
		constant(p_constant),
		linear(p_linear),
		quadratic(p_quadratic)
	{
		componentType = SPOT_LIGHT;
		ambient = p_initLight.ambient;
		diffuse = p_initLight.diffuse;
		specular = p_initLight.specular;
	}

	void SpotLight::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (outerCutOff < cutOff)
		{
			outerCutOff = cutOff + 0.00001f;
		}
		projectionMatrix = Math::Mat4::GetPerspectiveProjection(1.f, Math::DEG2RAD * outerCutOff * 2.f, 1.f, 1000.f);
		viewMatrix = Math::Mat4::LookAt(gameObject->transform.GetPosition(), gameObject->transform.GetPosition() + Math::Vector3(0.00001f, 0.0f, 0.00001f) + direction, Math::Vector3(0.f, 1.f, 0.f));
		Light::Update(p_deltaTime, p_inputs);
	}

	void SpotLight::DrawLight(const int p_shaderProgram, const Math::Vector3& p_camPosition, const unsigned int p_index) const
	{
		std::string array = "spotLights[" + std::to_string(p_index) + "].";

		Wrapper::RHI::SetIntShader(p_shaderProgram, (array + "lightData." + "shadowMap").c_str(), id);
		Wrapper::RHI::SetVec3Shader(p_shaderProgram, (array + "direction").c_str(), direction);
		Wrapper::RHI::SetFloatShader(p_shaderProgram, (array + "cutOff").c_str(), cosf(cutOff * Math::DEG2RAD));
		Wrapper::RHI::SetFloatShader(p_shaderProgram, (array + "outerCutOff").c_str(), cosf(outerCutOff * Math::DEG2RAD));
		Wrapper::RHI::SetFloatShader(p_shaderProgram, (array + "constant").c_str(), constant);
		Wrapper::RHI::SetFloatShader(p_shaderProgram, (array + "linear").c_str(), linear);
		Wrapper::RHI::SetFloatShader(p_shaderProgram, (array + "quadratic").c_str(), quadratic);

		Light::DrawLight(p_shaderProgram, p_camPosition, array);
	}
}
