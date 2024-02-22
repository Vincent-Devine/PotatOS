#include "pch.h"
#include <MonoBehavior/Scripts/Jump.hpp>

namespace MonoBehavior::Script
{
	void JumpScript::Start(GAMESTATE* p_gameState)
	{
		colliderSet = false;
		cooldown = 1.5f;
		timer = cooldown;
		jumpOnce = false;
		timeVelocity = 1.5f;
		endJump = false;

		if (!colliderSet)
		{
			for (size_t i = 0; i < gameObject->components.size(); i++)
			{
				if (gameObject->components[i]->componentType == COMPONENT_TYPE::CAPSULE_COLLIDER)
				{
					collider = dynamic_cast<MonoBehavior::Physics::CapsuleCollider*>(gameObject->components[i]);
					colliderSet = true;
				}

			}
		}
	}

	void JumpScript::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (colliderSet && p_inputs.jump && !jumpOnce)
		{
			jumpOnce = true;
		}

		timer += p_deltaTime;
		timerVelocity += p_deltaTime;
		if (jumpOnce)
		{
			if (endJump)
			{
				collider->AddForce(Math::Vector3(0.0f, 12.0f, 0.0f), true); 
				jumpOnce = false;
				timer = 0.f;
				timerVelocity = 0.f;
				collider->AddForce(Math::Vector3(0.0f, -2.0f, 0.0f), true);
				endJump = false;
			}
			jumpOnce = false;
		}

		Math::Vector3 currentVelocity = collider->GetVelocity();
		if (timerVelocity > timeVelocity && currentVelocity.y > lastVelocityY)
		{
			collider->SetVelocity(Math::Vector3(currentVelocity.x, 0, currentVelocity.z));
			endJump = true;
		}
		lastVelocityY = currentVelocity.y;

	}
}