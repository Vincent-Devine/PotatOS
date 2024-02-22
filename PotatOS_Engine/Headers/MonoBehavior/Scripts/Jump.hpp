#pragma once

#include <MonoBehavior/Scripts/BaseScript.hpp>
#include <MonoBehavior/IComponent.hpp>
#include <DLLInclude.hpp>
#include <MonoBehavior/Physics/CapsuleCollider.hpp>

namespace MonoBehavior::Script
{
	class JumpScript : public BaseScript
	{
	private:
		MonoBehavior::Physics::CapsuleCollider* collider;
		bool colliderSet;
		Math::Vector3 tempRot;
		float cooldown;
		float timer;
		bool jumpOnce;
		bool endJump;

		float lastVelocityY;
		float timerVelocity;
		float timeVelocity;

	public:
		void Start(GAMESTATE* p_gameState) override;
		void Update(const float p_deltaTime, const Inputs& p_inputs) override;
	};

}