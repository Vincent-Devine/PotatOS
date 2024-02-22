#include "pch.h"
#include <MonoBehavior/ColliderPlayerAttack.hpp>
#include <MonoBehavior/LifeScript.hpp>

namespace MonoBehavior
{
	void ColliderPlayerAttack::Start(GAMESTATE* p_gameState)
	{
		componentType = SCRIPT;
		gameState = p_gameState;
	}

	void ColliderPlayerAttack::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (!PtrCheck())
		{
			return;
		}

		if (playerAttack->GetIsAttacking() && boxCollider->Overlap().size() != 0)
		{
			for (OverlapHit& hit : boxCollider->Overlap())
			{
				LifeScript* targetLifeScript = hit.object->GetComponent<LifeScript>();
				if (targetLifeScript)
				{
					targetLifeScript->TakeDamage(1);
				}
			}
		}
	}

	bool ColliderPlayerAttack::PtrCheck()
	{
		if (playerAttack && boxCollider)
		{
			return true;
		}

		if (!playerAttack)
		{
			playerAttack = gameObject->Find("Player")->GetComponent<PlayerAttack>();
		}

		if (!boxCollider)
		{
			boxCollider = gameObject->GetComponent<Physics::BoxCollider>();
		}

		return playerAttack && boxCollider;
	}
}