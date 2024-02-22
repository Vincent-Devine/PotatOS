#pragma once

#include <MonoBehavior/IComponent.hpp>
#include <Math/Vector3.hpp>
#include <MonoBehavior/PlayerAttack.hpp>
#include <MonoBehavior/Physics/Collider.hpp>
#include <MonoBehavior/LifeScript.hpp>

namespace MonoBehavior
{
	class MoveCamera : public IComponent
	{
	// Attributes
	private:
		float* speed;
		Math::Vector3* rotation = nullptr;

		float curTime;
		float totalSlerpTime;
		Math::Quaternion startingRotation;
		Math::Quaternion desiredRotation;

		MonoBehavior::Physics::Collider* col = nullptr;

		PlayerAttack* playerAttack;
		MonoBehavior::LifeScript* lifeScript = nullptr;
		float MOVE_SPEED;

	// Methods
	public:
		void Start(GAMESTATE* p_gameState) override;
		void Update(const float p_deltaTime, const Inputs& p_inputs) override;

	private:
		bool PtrCheck();
	};
}
