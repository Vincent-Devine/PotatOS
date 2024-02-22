#pragma once

#include <DLLInclude.hpp>
 
#include <MonoBehavior/Renderer/Light.hpp>
#include <Refureku/Generated/SpotLight.rfkh.h>

namespace MonoBehavior::Renderer RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API SpotLight : public Light
	{
	// Attribute
	private:
		RFKField()
		Math::Vector3 direction;

		RFKField()
		float cutOff;

		RFKField()
		float outerCutOff;

		RFKField()
			float constant;

		RFKField()
			float linear;

		RFKField()
			float quadratic;

	// Method
	public:
		SpotLight(const InitLight& p_initLight, const Math::Vector3& p_direction, const float p_cutOff, const float p_outerCutOff, const float p_constant, const float p_linear, const float p_quadratic);
		void Update(const float p_deltaTime, const Inputs & p_inputs) override;
		void DrawLight(const int p_shaderProgram, const Math::Vector3& p_camPosition, const unsigned int p_index) const;
	
		const Math::Vector3& GetDirection() const { return direction; };
		const float GetCutOff() const { return cutOff; };
		const float GetOuterCutOff() const { return outerCutOff; };

		const float GetConstant() const { return constant; };
		const float GetLinear() const { return linear; };
		const float GetQuadratic() const { return quadratic; };

		MonoBehavior_Renderer_SpotLight_GENERATED
	};
}
File_SpotLight_GENERATED