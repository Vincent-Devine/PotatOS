#include "pch.h"
#include <MonoBehavior/LifeScript.hpp>

namespace MonoBehavior
{
	void LifeScript::Start(GAMESTATE* p_gameState)
	{
		componentType = SCRIPT;
		gameState = p_gameState;
		invinsible = false;
		timer = 0.f;
		invinsibleTime = 2.f;
		maxLife = 2;
		life = maxLife;
	}

	void LifeScript::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (invinsible)
		{
			timer += p_deltaTime;

			if (timer >= .2f)
			{
				tookDamage = false;
			}

			if (timer >= invinsibleTime)
			{
				timer = 0.f;
				invinsible = false;
			}
		}
	}

	void LifeScript::TakeDamage(int p_damage)
	{
		if (invinsible || life <= 0)
		{
			return;
		}

		life -= p_damage;
		invinsible = true;
		tookDamage = true;
	}
}
 