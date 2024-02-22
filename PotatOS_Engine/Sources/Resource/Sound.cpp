#include "pch.h"

#include <Resource/Sound.hpp>

namespace Resource
{
	Sound::Sound(const unsigned int p_id, const std::string& p_path)
	{
		id = p_id;
		index = 0;
		path = p_path;

		CreateName();
	}

	Sound::Sound(Sound& p_sound)
	{
		usedBy = 0;
		id = p_sound.id;
		index = 0;
		path = p_sound.path;
	}

	const bool Sound::Init()
	{
		isFinishToInit = false;
		Wrapper::SoundLayer::Get()->InitSound(path);
		index = Wrapper::SoundLayer::Get()->GetSoundIndex();
		isFinishToInit = true;

		return true;
	}

}