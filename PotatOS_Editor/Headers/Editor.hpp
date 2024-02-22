#pragma once

#include <Core/Engine.hpp>
#include <Wrapper/RHI.hpp>

#include "UILayer.hpp"
#include "GraphScene.hpp"
#include "Inspector.hpp"
#include "AudioMixerUI.hpp"
#include "Viewport.hpp"
#include "Assets.hpp"
#include "Guizmo.hpp"

namespace UI
{
	class Editor
	{
		// Attributes
	private:
		Core::Engine& engine;
		Wrapper::RHI& rhi;
		Wrapper::Window& window;
		Input::InputManager& inputManager;

		Wrapper::UILayer uiLayer;

		SceneGraph graphScene;
		Inspector inspector;
		AudioMixerUI audioMixerUI;
		Viewport viewport;
		Assets assets;
		Guizmo guizmo;
		ColorVisionDeficiency::VISION_TYPE* visionFilter;

		// Input
		int lastKeySInteraction;
		KEY_TYPE* actionInputChange;
		bool remappedQuitEditor;

		// Play Button
		Resource::Texture* playIcon;
		Resource::Texture* pauseIcon;

		int item_current = 0;
		ImFont* font;

		// Methods
	public:
		Editor(Core::Engine& p_engine, Wrapper::RHI& p_rhi, Wrapper::Window& p_window, Input::InputManager& p_inputManager);

		void Init();
		void Update();
		void Render();
		void Destroy();

	private:
		void SetDockSpace(bool p_open);
		void DisplayMenu();
		void EditMenu();

		void Toolbar();

		void PlayButton();

		void Input();
	};
}
