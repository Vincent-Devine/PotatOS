#include "pch.h"

#include <MonoBehavior/Scripts/ZombieFollowAttack.hpp>
#include <MonoBehavior/Physics/Collider.hpp>
#include <DebugSystem/Log.hpp>

namespace MonoBehavior::Script
{
	void ZombieFollowAttack::Start(GAMESTATE* p_state)
	{
		IComponent::Start(p_state);
		speed = 5.f;
		smellingRange = 15.f;
		attackRange = 3.5f;
		minRange = 3.f;
		timer = 0.f;
		attackReloadTime = .5f;
		attackDamage = 1;
		followPlayer = false;
		playerRangeAttack = false;

	}

	void ZombieFollowAttack::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (!PtrCheck() || *gameState == GAMESTATE::EDIT || !lifeScript->IsAlive())
		{
			playerRangeAttack = false;
			return;
		}

		Math::Vector3 dirToPlayer = playerTransform->GetPosition() - transform->GetPosition();
		float distance = Math::Vector3::Magnitude(dirToPlayer);
		dirToPlayer.y = 0.f;
		dirToPlayer = Math::Vector3::Normalize(dirToPlayer);

		if (distance > smellingRange)
		{
			followPlayer = false;
			playerRangeAttack = false;
			return;
		}
		followPlayer = true;


		transform->SetRotation(Math::Quaternion::QuatFromEuler(Math::Vector3(0.f, atan2f(dirToPlayer.x, dirToPlayer.z) * Math::RAD2DEG, 0.f)));
		
		if (distance > minRange)
		{
			transform->SetPosition(transform->GetLocalPosition() + dirToPlayer * p_deltaTime * speed);
			transform->Update();
			col->SetModified();
		}

		if (distance > attackRange)
		{
			playerRangeAttack = false;
			return;
		}

		timer += p_deltaTime;

		if (timer < attackReloadTime)
		{
			playerRangeAttack = false;
			return;
		}

		timer = 0.f;
		playerRangeAttack = true;
		playerLifeScript->TakeDamage(attackDamage);
	}

	bool ZombieFollowAttack::PtrCheck()
	{
		if (!transform)
		{
			transform = &gameObject->transform;
		}

		if (!col)
		{
			col = gameObject->GetCollider();
		}

		if (!playerTransform)
		{
			playerTransform = &gameObject->Find("Player")->transform;
		}

		if (!lifeScript)
		{
			lifeScript = gameObject->GetComponent<LifeScript>();
		}

		if (playerTransform && !playerLifeScript)
		{
			playerLifeScript = playerTransform->gameObject->GetComponent<LifeScript>();
		}

		return transform && col && playerTransform && lifeScript && playerLifeScript;
	}
}
