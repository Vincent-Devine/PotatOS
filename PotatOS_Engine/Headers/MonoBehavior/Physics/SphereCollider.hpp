#pragma once
#include <DLLInclude.hpp>

#include <MonoBehavior/Physics/Collider.hpp>
#include <Refureku/Refureku.h>
#include <Refureku/Generated/SphereCollider.rfkh.h>

namespace MonoBehavior::Physics RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API SphereCollider : public Collider
	{
		// Attributes
	private:
		RFKField()
		float radius;

		// Methods
	public:
		SphereCollider(const float p_radius = 1.f, const bool p_static = true, const bool p_trigger = false, const bool p_queryShape = false, const Math::Vector3& p_offset = Math::Vector3());

		void Start(GAMESTATE * p_gameState) override;

		const float GetRadius() const { return radius; };

		void SetRadius();

		MonoBehavior_Physics_SphereCollider_GENERATED
	};
}

File_SphereCollider_GENERATED
