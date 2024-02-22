#include "Viewport.hpp"
#include <ImGUI/Include/imgui.h>

namespace UI
{
	void Viewport::Draw(Wrapper::RHI& p_rhi, Guizmo& p_guizmo, DataStructure::GameObject* p_gameObjectSelected, Math::Vector2& windowSize)
	{
		ImGui::Begin("GameWindow");
		{
			fps = ImGui::GetIO().Framerate;
			fpsHistory.push_back(fps);

			if (fpsHistory.size() > maxHistorySize)
			{
				fpsHistory.erase(fpsHistory.begin());
			}

			const ImVec2 size = ImGui::GetContentRegionAvail();
			windowSize = Math::Vector2(size.x, size.y);
			ImGui::Image((ImTextureID)(p_rhi.GetTextureToRender()), size, {0.f, 1.f}, {1.f, 0.f});

			p_guizmo.Draw(p_gameObjectSelected);
		}
		ImGui::End();

		ImGui::Begin("Performance");
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.f, 1.f, 0.f, 1.f));
			ImGui::Text(" %.1f FPS", fps);
			ImGui::PopStyleColor(1);

			ImGui::PlotLines("FPS", fpsHistory.data(), fpsHistory.size(), 0, nullptr, 0.0f, 200.0f, ImVec2(0, 80));

		}
		ImGui::End();

	}
}
