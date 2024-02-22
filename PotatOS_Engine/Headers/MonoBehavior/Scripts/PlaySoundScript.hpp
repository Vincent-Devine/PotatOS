#pragma once

#include <DLLInclude.hpp>
#include <MonoBehavior/AudioSource.hpp>
#include <MonoBehavior/Canva.hpp>
#include <MonoBehavior/Scripts/BaseScript.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/PlaySoundScript.rfkh.h>

namespace MonoBehavior RFKNamespace()
{
	namespace Script RFKNamespace()
	{
		class RFKClass() POTATOS_ENGINE_API PlaySoundScript : public BaseScript
		{
		private :
			RFKField()
			MonoBehavior::Canva* canva;

			RFKField()
			MonoBehavior::AudioSource* audioSource;

			RFKField()
			std::string soundName;

			bool canvaSet;
			bool AudioSourceSet;
			float increment;
			bool doOnce;

		public :
			PlaySoundScript();
			void Start(GAMESTATE* p_gameState) override;
			void Update(const float p_deltaTime, const Inputs & p_inputs) override;

			MonoBehavior_Script_PlaySoundScript_GENERATED
		};
	}
}

File_PlaySoundScript_GENERATED