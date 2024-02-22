#include "pch.h"

#include <MonoBehavior/Scripts/PlaySoundScript.hpp>

namespace MonoBehavior::Script
{
	PlaySoundScript::PlaySoundScript()
	{
		componentType = SCRIPT;
	}

	void PlaySoundScript::Start(GAMESTATE* p_gameState)
	{
		gameState = p_gameState;
		doOnce = false;

		if (!canvaSet && !AudioSourceSet)
		{
			for (size_t i = 0; i < gameObject->components.size(); i++)
			{
				if (gameObject->components[i]->componentType == COMPONENT_TYPE::AUDIOSOURCE)
				{
					audioSource = (MonoBehavior::AudioSource *)gameObject->components[i];
					soundName = audioSource->GetSoundName();
					AudioSourceSet = true;
				}
				else if (gameObject->components[i]->componentType == COMPONENT_TYPE::CANVA)
				{
					canva = (MonoBehavior::Canva*)gameObject->components[i];
					canva->SetText(soundName.c_str());
					canvaSet = true;
					increment = canva->GetTimer();
				}
			}
		}

	}

	void PlaySoundScript::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (!canvaSet || !AudioSourceSet)
		{
			return;
		}

		if (!doOnce && *gameState == GAMESTATE::PLAY && gameObject->GetName() == "Player" && p_inputs.attack)
		{
			doOnce = true;
			increment = 0.f;
			audioSource->PlayAudioSource();
		}
		increment += p_deltaTime;

		if (increment < canva->GetTimer())
		{
			canva->SetText((soundName + " is playing").c_str());
			canva->hide = false;
		}
		else
		{
			doOnce = false;
			canva->hide = true;
		}
	
	}

}
