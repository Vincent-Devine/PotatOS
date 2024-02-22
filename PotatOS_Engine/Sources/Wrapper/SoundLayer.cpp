#include "pch.h"
#include "Wrapper/SoundLayer.hpp"

#include <iostream>

namespace Wrapper
{
	SoundLayer* SoundLayer::singleton = nullptr;

	SoundLayer::SoundLayer()
	{
		nbChannels = 6;
		extradriverdata = 0;
		volumeGlobal = 1.f;
		soundIndex = -1;

		lastpos = { 0.f, 0.f, 0.f };
		forward = { 0.f, 0.f, 1.f };
		up = { 0.f, 1.f, 0.f };

		time = 0;
		channelsplaying = 0;

		FMOD::System_Create(&system);
		system->getVersion(&version);
		if (version < FMOD_VERSION)
		{
			std::cout << "FMOD lib version doesn't match header version";
		}

		system->init(nbChannels, FMOD_INIT_NORMAL, extradriverdata);
		system->set3DSettings(1.0, DISTANCEFACTOR, 1.0f);
		system->getMasterChannelGroup(&channelGroupGlobal);

		FMOD_VECTOR position = { 0.f, 0.f, 0.f };
		FMOD_VECTOR velocity = { 0.f, 0.f, 0.f };

		for (size_t i = 0; i < nbChannels; i++)
		{
			channels[i] = 0;
			channels[i]->set3DAttributes(&position, &velocity);
			channels[i]->setChannelGroup(channelGroupGlobal);
			channelsPitches[i] = 1.f;
			channels[i]->setPitch(channelsPitches[i]);
			channelsVolume[i] = 1.f;
			channels[i]->setVolume(channelsVolume[i]);
			channelSet2D[i] = false;
			channels[i]->setMode(FMOD_3D_WORLDRELATIVE);
			channels[i]->setMode(FMOD_3D_LINEARSQUAREROLLOFF);
		}

	}

	SoundLayer::~SoundLayer()
	{
		for (size_t i = 0; i <= soundIndex; i++)
		{
			if (soundInfos[i]->sound != nullptr)
			{
				soundInfos[i]->sound->release();
			}
		}

		system->close();
		system->release();
	}

	void SoundLayer::Update(const Math::Vector3& p_posCam)
	{
		system->update();
		CalcAttenuation(p_posCam);
		system->getChannelsPlaying(&channelsplaying, NULL);

	}

	void SoundLayer::Play3D(const Math::Vector3& p_soundPos, const int p_indexSoundToPlay, const int p_indexChannel, bool p_loop, float min, float max)
	{
		if (p_loop)
		{
			soundInfos[p_indexSoundToPlay]->sound->setMode(FMOD_LOOP_NORMAL);
			channels[p_indexChannel]->setMode(FMOD_3D_HEADRELATIVE);
		}
		else
		{
			soundInfos[p_indexSoundToPlay]->sound->setMode(FMOD_INIT_NORMAL);
			channels[p_indexChannel]->setMode(FMOD_3D_WORLDRELATIVE);

		}
		FMOD_VECTOR position = { p_soundPos.x, p_soundPos.y, p_soundPos.z };
		FMOD_VECTOR velocity = { 1.f, 1.f, 1.f };
		soundInfos[p_indexSoundToPlay]->sound->set3DMinMaxDistance(min * DISTANCEFACTOR, max * DISTANCEFACTOR);
		system->playSound(soundInfos[p_indexSoundToPlay]->sound, 0, false, &channels[p_indexChannel]);
		channels[p_indexChannel]->set3DAttributes(&position, &velocity);
	}

	void SoundLayer::ResetPosLoop(const Math::Vector3& p_soundPos, const int p_indexSoundToPlay, const int p_indexChannel)
	{
		soundInfos[p_indexSoundToPlay]->sound->setMode(FMOD_LOOP_NORMAL);
		FMOD_VECTOR position = { p_soundPos.x, p_soundPos.y, p_soundPos.z };
		FMOD_VECTOR velocity = { 0.f, 0.f, 0.f };
		channels[p_indexChannel]->set3DAttributes(&position, &velocity);
	}

	void SoundLayer::Switch2DTo3D(int p_channelIndex)
	{
		if (channelSet2D[p_channelIndex] == true)
		{
			channels[p_channelIndex]->setMode(FMOD_3D_HEADRELATIVE);
		}
		else
		{
			channels[p_channelIndex]->setMode(FMOD_3D_WORLDRELATIVE);
		}
	}

	void SoundLayer::SetGlobalVolume()
	{
		channelGroupGlobal->setVolume(volumeGlobal);
	}

	void SoundLayer::SetChannelVolume(int p_channelIndex)
	{
		channels[p_channelIndex]->setVolume(channelsVolume[p_channelIndex]);
	}

	void SoundLayer::PreventOverlap(int p_channelIndex)
	{
		channels[p_channelIndex]->isPlaying(&finishedPlaying);
	}

	void SoundLayer::CalcAttenuation(const Math::Vector3& p_posCam)
	{
		listenerpos = { p_posCam.x, p_posCam.y, p_posCam.z };

		// left right pingpong
		/*if (listenerflag)
		{
			listenerpos.x = (float)sin(t * 0.05f) * 24.0f * DISTANCEFACTOR; 
		}*/

		// How far we moved last FRAME (m/f), then time compensate it to SECONDS (m/s).
		vel.x = (listenerpos.x - lastpos.x) * (1000 / INTERFACE_UPDATETIME);
		vel.y = (listenerpos.y - lastpos.y) * (1000 / INTERFACE_UPDATETIME);
		vel.z = (listenerpos.z - lastpos.z) * (1000 / INTERFACE_UPDATETIME);

		lastpos = listenerpos;
		system->set3DListenerAttributes(0, &listenerpos, &vel, &forward, &up);
		// t is just a time value .. it increments in 30m/s steps in this example
		time += (30 * (1.0f / (float)INTERFACE_UPDATETIME));    
	}

	void SoundLayer::InitSound(const std::string& p_path)
	{
		std::lock_guard guard(soundCreatingMutex);
		soundIndex++;
		FMOD::Sound *temp;
		system->createSound(p_path.c_str(), FMOD_3D, 0, &temp);
		soundInfos.push_back(new AudioSourceInfos{ temp, std::filesystem::u8path(p_path).stem().u8string() });
		soundInfos[soundIndex]->sound->setMode(FMOD_3D_LINEARSQUAREROLLOFF);
		soundInfos[soundIndex]->sound->setMode(FMOD_LOOP_OFF);
		soundInfos[soundIndex]->sound->set3DMinMaxDistance(MIN_HEARING_DISTANCE * DISTANCEFACTOR, MAX_HEARING_DISTANCE * DISTANCEFACTOR);

	}

	void SoundLayer::PauseSound()
	{
		pauseSound = !pauseSound;
		channelGroupGlobal->setPaused(pauseSound);
	}

	void SoundLayer::SetChannelPitch(int p_channelIndex)
	{
		channels[p_channelIndex]->setPitch(channelsVolume[p_channelIndex]);
	}

	SoundLayer* SoundLayer::Get()
	{
		if (singleton == nullptr)
		{
			singleton = new SoundLayer;
		}
		return singleton;
	}

}