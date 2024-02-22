#pragma once
#include <DLLInclude.hpp>

#include <MonoBehavior/Physics/Collider.hpp>
#include <Refureku/Refureku.h>
#include <Refureku/Generated/CapsuleCollider.rfkh.h>

namespace MonoBehavior::Physics RFKNamespace()
{
	
	enum class RFKEnum() AXIS_ALIGNMENT : int
	{
		X,
		Y,
		Z
	};
	class RFKClass() POTATOS_ENGINE_API CapsuleCollider : public Collider
	{
		// Attributes
	private:
		RFKField()
		float radius;

		RFKField()
		AXIS_ALIGNMENT alignment;
		
		RFKField()
		float halfHeight;

		// Methods
	public:
		CapsuleCollider(
			const float p_radius = 1.f, const AXIS_ALIGNMENT p_alignment = MonoBehavior::Physics::AXIS_ALIGNMENT::Y, const float p_halfHeight = 2.f,
			const bool p_static =  false, const bool p_trigger = false, const bool p_queryShape = false, const Math::Vector3& p_offset = Math::Vector3()
		);

		void Start(GAMESTATE* p_gameState) override;

		void SetHalfHeight();
		void SetRadius();

		void SetTilt();
		float GetHalfHeight() const { return halfHeight; };
		const float GetRadius() const { return radius; };
		const AXIS_ALIGNMENT GetAlignment() const { return alignment; };
		void SetAlignment(const int p_alignment);

		MonoBehavior_Physics_CapsuleCollider_GENERATED
	};
}

File_CapsuleCollider_GENERATED