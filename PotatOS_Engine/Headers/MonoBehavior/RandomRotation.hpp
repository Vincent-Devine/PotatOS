#pragma once

#include <DLLInclude.hpp>
#include <MonoBehavior/IComponent.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/RandomRotation.rfkh.h>

namespace RFKNamespace() MonoBehavior
{
	class RFKClass() POTATOS_ENGINE_API RandomRotation : public IComponent
	{
	// Attributes
	private:

		RFKField()
		unsigned int timer;

		unsigned int timeNewRotation;

		Math::Vector3 rotation;
		Math::Quaternion startingRotation;
		Math::Quaternion desiredRotation;
		float t;

		RFKField()
		float speed;

	// Methods
	public:
		RandomRotation();

		void Start(GAMESTATE* p_gameState) override;
		void Update(const float p_deltaTime, const Inputs& p_inputs) override;

		//MonoBehavior_RandomRotation_GENERATED
	};
}
File_RandomRotation_GENERATED