#pragma once
#include <DLLInclude.hpp>

#include <MonoBehavior/Physics/Collider.hpp>
#include <Refureku/Refureku.h>
#include <Refureku/Generated/BoxCollider.rfkh.h>

namespace MonoBehavior::Physics RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API BoxCollider : public Collider
	{
		// Attributes
	private:
		RFKField()
		Math::Vector3 scale;

		// Methods
	public:
		BoxCollider(const Math::Vector3& p_scale = Math::Vector3::One(), const bool p_static = true, const bool p_trigger = false, const bool p_queryShape = false, const Math::Vector3& p_offset = Math::Vector3());

		void Start(GAMESTATE * p_gameState) override;

		const Math::Vector3& GetScale() const { return scale; };

		void SetScale();

		MonoBehavior_Physics_BoxCollider_GENERATED
	};
}

File_BoxCollider_GENERATED