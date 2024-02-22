#pragma once

#include <Common.hpp>
#include <Wrapper/Window.hpp>

namespace Input
{
	class InputManager
	{
	// Attributes
	private:
		static InputManager* singleton;

		double mouseX, mouseY;
		float mouseDeltaX, mouseDeltaY;
		bool mouseCaptured;
		unsigned int timeMouseCaptured;

	public:
		KEY_TYPE forward;
		KEY_TYPE backward;
		KEY_TYPE left;
		KEY_TYPE right;
		KEY_TYPE down;
		KEY_TYPE up;
		float sensitivity = 0.2f;

		KEY_TYPE gameForward;
		KEY_TYPE gameBackward;
		KEY_TYPE gameLeft;
		KEY_TYPE gameRight;
		KEY_TYPE gameJump;
		KEY_TYPE gameAttack;
		KEY_TYPE gameQuit;
		KEY_TYPE gameMenu;
		KEY_TYPE restart;

	// Methods
	public:
		static InputManager* Get();

		InputManager();

		const Inputs Update(const Wrapper::Window& p_window, const GAMESTATE p_gameState);
	
	private:
		void InputKeyBoard(Inputs& p_inputs, const Wrapper::Window& p_window, const GAMESTATE p_gameState);
		void InputMouse(Inputs& p_inputs, const Wrapper::Window& p_window, const GAMESTATE p_gameState);
		void InputGamepad(Inputs& p_inputs, const Wrapper::Window& p_window, const GAMESTATE p_gameState);

		void DefaultValueGamepad(Inputs& p_inputs);
	};
}
