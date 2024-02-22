#include "pch.h"

#include <MonoBehavior/Renderer/PointLight.hpp>
#include <Wrapper/RHI.hpp>

namespace MonoBehavior::Renderer
{
	PointLight::PointLight(const InitLight& p_initLight, const float p_constant, const float p_linear, const float p_quadratic):
		constant(p_constant),
		linear(p_linear),
		quadratic(p_quadratic)
	{
		componentType = POINT_LIGHT;
		ambient = p_initLight.ambient;
		diffuse = p_initLight.diffuse;
		specular = p_initLight.specular;
	}

	void PointLight::DrawLight(const int p_shaderProgram, const Math::Vector3& p_camPosition, const unsigned int p_index) const
	{
		std::string array = "pointLights[" + std::to_string(p_index) + "].";

		Wrapper::RHI::SetFloatShader(p_shaderProgram, (array + "constant").c_str(), constant);
		Wrapper::RHI::SetFloatShader(p_shaderProgram, (array + "linear").c_str(), linear);
		Wrapper::RHI::SetFloatShader(p_shaderProgram, (array + "quadratic").c_str(), quadratic);

		Light::DrawLight(p_shaderProgram, p_camPosition, array);
	}
}
