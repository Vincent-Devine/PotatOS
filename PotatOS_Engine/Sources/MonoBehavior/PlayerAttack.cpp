#include "pch.h"

#include <MonoBehavior/PlayerAttack.hpp>
#include <MonoBehavior/Scripts/PlaySoundScript.hpp>

namespace MonoBehavior
{
	void PlayerAttack::Start(GAMESTATE* p_gameState)
	{
		componentType = SCRIPT;
		gameState = p_gameState;
		speedInAttack = .5f;

		playSoundScript = gameObject->GetComponent<MonoBehavior::Script::PlaySoundScript>();		
	}
}