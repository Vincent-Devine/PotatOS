#pragma once
#include <DLLInclude.hpp>
#include <string>
#include <fmod.hpp>
#include <fmod_common.h>
#include <Math/Vector3.hpp>
#include <Math/Vector2.hpp>
#include <vector>
#include <filesystem>
#include <mutex>

namespace Wrapper
{
	struct AudioSourceInfos
	{
		FMOD::Sound* sound;
		std::string name;
	};

	class POTATOS_ENGINE_API SoundLayer
	{
	public:
		float volumeGlobal;

		//TO DO Create struct
		FMOD::Channel* channels[6];
		float channelsVolume[6];
		float channelsPitches[6];
		bool channelSet2D[6];

		std::vector<AudioSourceInfos*> soundInfos;

		bool finishedPlaying;
		float MIN_HEARING_DISTANCE = 0.5f;
		float MAX_HEARING_DISTANCE = 100.f;

	private :
		static SoundLayer* singleton;

		FMOD::System* system;
		FMOD_RESULT result;
		unsigned int version;
		void* extradriverdata;

		int nbChannels;
		int channelsplaying;
		bool listenerflag = true;

		const float DISTANCEFACTOR = 1.0f;
		const int INTERFACE_UPDATETIME = 50;

		FMOD_VECTOR listenerpos;
		FMOD_VECTOR lastpos, forward, up, vel;
		Math::Vector3 camPos;
		float time;

		int soundIndex;

		bool pauseSound;
		FMOD::ChannelGroup * channelGroupGlobal;
		std::mutex soundCreatingMutex;

	public:
		SoundLayer();
		~SoundLayer();
		static SoundLayer* Get();
		void Update(const Math::Vector3& posCam);

		void InitSound(const std::string& p_Path);
		void PauseSound();
		void SetGlobalVolume();
		void SetChannelVolume(int p_channelIndex);
		void SetChannelPitch(int p_channelIndex);
		void Switch2DTo3D(int p_channelIndex);
		void Play3D(const Math::Vector3& p_soundPos, const int p_indexSoundToPlay, const int p_indexChannel, bool p_loop, float min, float max);
		void ResetPosLoop(const Math::Vector3& p_soundPos, const int p_indexSoundToPlay, const int p_indexChannel);
		const int GetSoundIndex() const { return soundIndex; };

	private:
		void PreventOverlap(int p_channelIndex);
		void CalcAttenuation(const Math::Vector3& posCam);

	};

}