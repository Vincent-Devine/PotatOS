#pragma once

#include <ImGUI/Include/imgui.h>
#include <Wrapper/SoundLayer.hpp>

namespace UI
{
	class AudioMixerUI
	{
		// Attributes
	private:
		Wrapper::SoundLayer* soundLayer;
	
	public : 
		int indexSelected;
		// Methods
	private:
		void PauseSound();
		void VolumeSlider();
		void DrawChannels();

	public:
		void Draw();

	};
}
