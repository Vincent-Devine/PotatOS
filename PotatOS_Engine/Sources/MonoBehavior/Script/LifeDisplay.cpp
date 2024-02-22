#include "pch.h"

#include <MonoBehavior/Scripts/LifeDisplay.hpp>
#include <MonoBehavior/Scripts/MenuScript.hpp>
#include <MonoBehavior/Physics/Collider.hpp>

namespace MonoBehavior::Script
{
	bool LifeDisplay::gameOver = false;

	void LifeDisplay::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (!PtrCheck())
		{
			return;
		}

		if (*gameState == GAMESTATE::EDIT)
		{
			canva->hide = true;
		}
		else
		{
			canva->hide = MonoBehavior::Script::MenuScript::showMenu;
		}

		if (CheckWin())
		{
			canva->SetText("You won!");
			Math::Vector2 temp = { -200.f, 0.f };
			canva->SetPos(temp);
			gameOver = true;
		}
		else if (playerLifeScript->IsAlive())
		{
			canva->SetText((std::to_string(playerLifeScript->GetLifePoints()) + "HP").c_str());
		}
		else
		{
			Math::Vector2 temp = { -200.f, 0.f };
			canva->SetPos(temp);
			canva->SetText("Game Over");
			gameOver = true;
		}
	}

	bool LifeDisplay::CheckWin()
	{
		std::vector<OverlapHit> hits = finishCollider->Overlap();
		if (hits.size() <= 0)
		{
			return false;
		}

		for (OverlapHit hit : hits)
		{
			if (hit.object->GetName() == "Player")
			{
				return true;
			}
		}

		return false;
	}

	bool LifeDisplay::PtrCheck()
	{
		if (!canva)
		{
			DataStructure::GameObject* canvaP = gameObject->Find("CanvaPlayer");
			if (canvaP)
			{
				canva = canvaP->GetComponent<Canva>();
			}
		}

		if (!finishCollider)
		{
			DataStructure::GameObject* finishCube = gameObject->Find("Flag");
			if (finishCube)
			{
				finishCollider = finishCube->GetComponent<MonoBehavior::Physics::Collider>();
			}
		}

		if (!playerLifeScript)
		{
			playerLifeScript = gameObject->GetComponent<LifeScript>();
		}

		return canva && playerLifeScript && finishCollider;
	}
}