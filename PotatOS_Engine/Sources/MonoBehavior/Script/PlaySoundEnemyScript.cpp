#include "pch.h"

#include <MonoBehavior/Scripts/PlaySoundEnemyScript.hpp>

namespace MonoBehavior::Script
{
	PlaySoundEnemyScript::PlaySoundEnemyScript()
	{
		componentType = SCRIPT;
	}

	void PlaySoundEnemyScript::Start(GAMESTATE* p_gameState)
	{
		gameState = p_gameState;
		doOnce = false;
		playEnemySound = false;

		if (!canvaSet && !AudioSourceSet)
		{
			for (size_t i = 0; i < gameObject->components.size(); i++)
			{
				if (gameObject->components[i]->componentType == COMPONENT_TYPE::AUDIOSOURCE)
				{
					audioSource = (MonoBehavior::AudioSource*)gameObject->components[i];
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

	void PlaySoundEnemyScript::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (!canvaSet || !AudioSourceSet)
		{
			return;
		}

		if (!doOnce && *gameState == GAMESTATE::PLAY && playEnemySound)
		{
			doOnce = true;
			increment = 0.f;
			audioSource->PlayAudioSource();
			playEnemySound = false;
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
