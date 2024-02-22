#pragma once

#include <DLLInclude.hpp>
#include <MonoBehavior/IComponent.hpp>
#include <Resource/Sound.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/AudioSource.rfkh.h>

namespace MonoBehavior RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API AudioSource : public IComponent
	{
		// Attributes
	private:
		RFKField()
		int channel;

		RFKField()
		bool playOnLoop;

		RFKField()
		bool play;

		RFKField()
		Resource::Sound* sound;

		RFKField()
		float minRange;

		RFKField()
		float maxRange;

		Wrapper::SoundLayer* soundLayer;
		// Methods
	public:
		AudioSource();
		AudioSource(Resource::Sound* p_sound);
		AudioSource(Resource::Sound * p_sound, int p_channel, bool p_PlayOnLoop, float p_minRange, float p_maxRange);
		void Start(GAMESTATE * p_gameState) override;
		void Update(const float p_deltaTime, const Inputs& p_inputs) override;
		void Destroy() override;

		const char * GetSoundName() { return sound->GetName().c_str(); };
		const Resource::Sound* GetSound() const { return sound; };
		const int GetChannel() const { return channel; };
		const bool GetPlayOnLoop() const { return playOnLoop; };
		const float GetMinRange() const { return minRange; };
		const float GetMaxRange() const { return maxRange; };
		void PlayAudioSource() { play = true; };

		MonoBehavior_AudioSource_GENERATED
	};
}

File_AudioSource_GENERATED
