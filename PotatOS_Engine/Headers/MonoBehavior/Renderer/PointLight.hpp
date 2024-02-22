#pragma once

#include <DLLInclude.hpp>

#include <MonoBehavior/Renderer/Light.hpp>
#include <Refureku/Generated/PointLight.rfkh.h>

namespace MonoBehavior::Renderer RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API PointLight : public Light
	{
	// Attribute
	private:
		RFKField()
		float constant;

		RFKField()
		float linear;

		RFKField()
		float quadratic;

	// Method
	public:
		PointLight(const InitLight& p_initLight, const float p_constant, const float p_linear, const float p_quadratic);

		void DrawLight(const int p_shaderProgram, const Math::Vector3& p_camPosition, const unsigned int p_index) const;
	
		const float GetConstant() const { return constant; };
		const float GetLinear() const { return linear; };
		const float GetQuadratic() const { return quadratic; };

		MonoBehavior_Renderer_PointLight_GENERATED
	};
}
File_PointLight_GENERATED