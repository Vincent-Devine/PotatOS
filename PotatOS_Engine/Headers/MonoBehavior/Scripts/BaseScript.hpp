#pragma once

#include <DLLInclude.hpp>
#include <MonoBehavior/IComponent.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/BaseScript.rfkh.h>

namespace MonoBehavior RFKNamespace()
{
	namespace Script RFKNamespace()
	{
		class RFKClass() POTATOS_ENGINE_API BaseScript : public IComponent
		{
		private:
			RFKField()
			std::string scriptName;

		public:
			bool playSound;

		public:
			void Start(GAMESTATE * p_gameState) override;

			MonoBehavior_Script_BaseScript_GENERATED
		};
	}
}

File_BaseScript_GENERATED