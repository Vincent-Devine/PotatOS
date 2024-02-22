#include "pch.h"

#include <MonoBehavior/AudioSource.hpp>
#include <Core/ResourceManager.hpp>

namespace MonoBehavior
{
	AudioSource::AudioSource(Resource::Sound* p_sound, int p_channel, bool p_PlayOnLoop, float p_minRange, float p_maxRange)
		: sound(p_sound)
		, play(false)
		, playOnLoop(p_PlayOnLoop)
		, channel(p_channel)
	{
		componentType = AUDIOSOURCE;
		minRange = p_minRange;
		maxRange = p_maxRange;
	}

	AudioSource::AudioSource(Resource::Sound* p_sound)
		: sound(p_sound)
		, play(false)
		, playOnLoop(false)
		, channel(1)
	{
		componentType = AUDIOSOURCE;
		minRange = 0.5f;
		maxRange = 100.f;
	}

	AudioSource::AudioSource()
		: sound(nullptr)
		, play(false)
		, playOnLoop(false)
		, channel(1)
	{
		componentType = AUDIOSOURCE;
		minRange = 0.5f;
		maxRange = 100.f;
	}

	void AudioSource::Start(GAMESTATE* p_gameState)
	{
		gameState = p_gameState;
		soundLayer = Wrapper::SoundLayer::Get();
	}

	void AudioSource::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (play && *gameState == GAMESTATE::PLAY)
		{
			soundLayer->Play3D(gameObject->transform.GetPosition(), sound->index, channel, playOnLoop, minRange, maxRange);
			play = false;
		}

		if (playOnLoop && *gameState == GAMESTATE::PLAY && gameObject->transform.parentTransform)
		{
			soundLayer->ResetPosLoop(gameObject->transform.parentTransform->GetPosition(), sound->index, channel);
		}

	}


	void AudioSource::Destroy()
	{
		Core::ResourceManager* resourceManager = Core::ResourceManager::Get();

		Log::Print(sound->GetName() + " will be released", LOG_LEVEL_TYPE::Notification);
		resourceManager->StopUsedResource(sound);

	}
}

