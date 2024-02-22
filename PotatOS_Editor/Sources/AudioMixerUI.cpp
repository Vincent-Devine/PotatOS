#include "AudioMixerUI.hpp"

namespace UI
{  
	void AudioMixerUI::Draw()
	{
		soundLayer = Wrapper::SoundLayer::Get();
		ImGui::SetNextWindowSize(ImVec2(10.f, 10.f), ImGuiCond_FirstUseEver);
		ImGui::Begin("Audio Mix");
		PauseSound();
		VolumeSlider();
		DrawChannels();
		ImGui::End();
	}

	void AudioMixerUI::PauseSound()
	{
		if (ImGui::Button("PauseSound"))
		{
			soundLayer->PauseSound();
		}
	}

	void AudioMixerUI::VolumeSlider()
	{
		ImGui::SetNextItemWidth(250);
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.f, 0.f, 1.f, 0.35f));
		if (ImGui::SliderFloat("Global Volume", &soundLayer->volumeGlobal, 0.f, 2.f, "%.3f"))
		{
			soundLayer->SetGlobalVolume();
		}
		ImGui::PopStyleColor(1);
	}

	void AudioMixerUI::DrawChannels()
	{
		for (size_t i = 0; i < IM_ARRAYSIZE(soundLayer->channels); i++)
		{
			if (ImGui::TreeNode(("Channel " + std::to_string(i)).c_str()))
			{
				ImGui::SetNextItemWidth(250);
				if (ImGui::Checkbox(("Set to 2D " + std::to_string(i)).c_str(), &soundLayer->channelSet2D[i]))
				{
					soundLayer->channelSet2D[i] = !soundLayer->channelSet2D[i];
					soundLayer->Switch2DTo3D(i);
				}

				ImGui::SetNextItemWidth(250);
				ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.f, 0.f, 1.f, 0.35f));
				if (ImGui::SliderFloat(("Channel Volume " + std::to_string(i)).c_str(),&soundLayer->channelsVolume[i], 0.f, 5.f))
				{
					soundLayer->SetChannelVolume(i);
				}
				ImGui::PopStyleColor(1);

				ImGui::SetNextItemWidth(250);
				ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.f, 0.f, 1.f, 0.35f));
				if (ImGui::SliderFloat(("Channel Pitch " + std::to_string(i)).c_str(), &soundLayer->channelsPitches[i], 0.f, 5.f))
				{
					soundLayer->SetChannelVolume(i);
					soundLayer->SetChannelPitch(i);
				}
				ImGui::PopStyleColor(1);
				ImGui::TreePop();
			}
		}
	}
}
