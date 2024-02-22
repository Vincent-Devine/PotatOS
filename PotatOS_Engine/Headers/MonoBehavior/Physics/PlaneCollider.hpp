#pragma once
#include <DLLInclude.hpp>

#include <MonoBehavior/Physics/Collider.hpp>
#include <Refureku/Refureku.h>
#include <Refureku/Generated/PlaneCollider.rfkh.h>

namespace MonoBehavior::Physics RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API PlaneCollider : public Collider
	{
		// Methods
	public:
		PlaneCollider(const bool p_trigger = false, const bool p_queryShape = false);

		void Start(GAMESTATE * p_gameState) override;

		MonoBehavior_Physics_PlaneCollider_GENERATED
	};
}

File_PlaneCollider_GENERATED
