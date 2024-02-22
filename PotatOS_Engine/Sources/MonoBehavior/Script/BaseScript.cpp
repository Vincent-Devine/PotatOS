#include "pch.h"

#include <MonoBehavior/Scripts/BaseScript.hpp>

namespace MonoBehavior
{
	namespace Script
	{
		void BaseScript::Start(GAMESTATE* p_gameState)
		{
			componentType = SCRIPT;
			gameState = p_gameState;

		}

	}
}