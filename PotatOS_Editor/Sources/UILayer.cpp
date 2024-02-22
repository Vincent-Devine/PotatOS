#include "UILayer.hpp"

#include <ImGUI/Include/imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include <GLFW/glfw3.h>

#include "ImGuizmo/ImGuizmo.h"

namespace Wrapper
{
	void UILayer::Init(Window& p_window)
	{
		glfwInit();
		glfwMakeContextCurrent(p_window.window);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(p_window.window, true);
		ImGui_ImplOpenGL3_Init("#version 330"); // GLSL version
	}

	void UILayer::Update()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();
	}

	void UILayer::Draw() const
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void UILayer::Destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void UILayer::SetDocking(const char * p_windowName)
	{
		ImGui::Begin(p_windowName);
		ImGuiID dockspaceId = ImGui::GetID(p_windowName);

		ImGui::DockBuilderRemoveNode(dockspaceId);
		ImGui::DockBuilderAddNode(dockspaceId);
		ImGui::DockBuilderSetNodeSize(dockspaceId, ImGui::GetMainViewport()->Size);

		auto dockIdUp = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Up, 0.5f, nullptr, &dockspaceId);
		auto dockIdDown = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Down, 0.5f, nullptr, &dockspaceId);
		ImGui::DockBuilderDockWindow("Up", dockIdUp);
		ImGui::DockBuilderDockWindow("Down", dockIdDown);

		ImGui::DockBuilderFinish(dockspaceId);
		ImGui::End();
	}
}
