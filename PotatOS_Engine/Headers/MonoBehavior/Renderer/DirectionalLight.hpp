#pragma once

#include <DLLInclude.hpp>

#include <MonoBehavior/Renderer/Light.hpp>
#include <Refureku/Generated/DirectionalLight.rfkh.h>

namespace MonoBehavior::Renderer RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API DirectionalLight : public Light
	{
	// Attribute
	private:
		RFKField()
		Math::Vector3 direction;

	// Method
	public:
		DirectionalLight(const InitLight& p_initLight, const Math::Vector3& p_diretion);
		void Update(const float p_deltaTime, const Inputs & p_inputs) override;

		void DrawLight(const int p_shaderProgram, const Math::Vector3& p_camPosition, const unsigned int p_index) const;
	
		const Math::Vector3& GetDirection() const { return direction; };

		void SetPosition(const Math::Vector3& p_position) { gameObject->transform.SetPosition(p_position - 20.f * direction); gameObject->transform.Update(); };

		MonoBehavior_Renderer_DirectionalLight_GENERATED
	};
}
File_DirectionalLight_GENERATED