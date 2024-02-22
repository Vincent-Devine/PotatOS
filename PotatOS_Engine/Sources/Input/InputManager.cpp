#include "pch.h"

#include <Input/InputManager.hpp>
#include <DebugSystem/Assertion.hpp>
#include <Wrapper/Window.hpp>

namespace Input
{
	InputManager* InputManager::singleton = nullptr;

	InputManager* InputManager::Get()
	{
		if (singleton == nullptr)
		{
			singleton = new InputManager();
		}
		return singleton;
	}

	InputManager::InputManager()
		: forward(KEY_TYPE::KEY_W)
		, backward(KEY_TYPE::KEY_S)
		, left(KEY_TYPE::KEY_A)
		, right(KEY_TYPE::KEY_D)
		, down(KEY_TYPE::KEY_LEFT_SHIFT)
		, up(KEY_TYPE::KEY_SPACE)
		, gameForward(KEY_TYPE::KEY_W)
		, gameBackward(KEY_TYPE::KEY_S)
		, gameLeft(KEY_TYPE::KEY_A)
		, gameRight(KEY_TYPE::KEY_D)
		, gameJump(KEY_TYPE::KEY_SPACE)
		, gameAttack(KEY_TYPE::KEY_MOUSE_BUTTON_LEFT)
		, gameQuit(KEY_TYPE::KEY_O)
		, gameMenu(KEY_TYPE::KEY_M)
		, restart(KEY_TYPE::KEY_R)
	{
	}

	const Inputs InputManager::Update(const Wrapper::Window& p_window, const GAMESTATE p_gameState)
	{
		Inputs inputs;
		InputKeyBoard(inputs, p_window, p_gameState);
		InputMouse(inputs, p_window, p_gameState);
		InputGamepad(inputs, p_window, p_gameState);
		return inputs;
	}

	void InputManager::InputKeyBoard(Inputs& p_inputs, const Wrapper::Window& p_window, const GAMESTATE p_gameState)
	{
		if (GAMESTATE::EDIT == p_gameState)
		{
			p_inputs.moveForward = p_window.GetKey(forward, KEY_INTERACTION_TYPE::PRESS);

			p_inputs.moveBackward = p_window.GetKey(backward, KEY_INTERACTION_TYPE::PRESS);

			p_inputs.moveLeft = p_window.GetKey(left, KEY_INTERACTION_TYPE::PRESS);

			p_inputs.moveRight = p_window.GetKey(right, KEY_INTERACTION_TYPE::PRESS);

			p_inputs.pauseAnimation = p_window.GetKey(KEY_TYPE::KEY_P, KEY_INTERACTION_TYPE::RELEASE);

			p_inputs.moveDown = p_window.GetKey(down, KEY_INTERACTION_TYPE::PRESS);

			p_inputs.moveUp = p_window.GetKey(up, KEY_INTERACTION_TYPE::PRESS);

			p_inputs.showmenu = p_window.GetKey(gameMenu, KEY_INTERACTION_TYPE::PRESS);
		}
		else
		{
			p_inputs.moveForward = p_window.GetKey(gameForward, KEY_INTERACTION_TYPE::PRESS);

			p_inputs.moveBackward = p_window.GetKey(gameBackward, KEY_INTERACTION_TYPE::PRESS);

			p_inputs.moveLeft = p_window.GetKey(gameLeft, KEY_INTERACTION_TYPE::PRESS);

			p_inputs.moveRight = p_window.GetKey(gameRight, KEY_INTERACTION_TYPE::PRESS);

			p_inputs.attack = p_window.GetKey(gameAttack, KEY_INTERACTION_TYPE::PRESS);

			p_inputs.jump = p_window.GetKey(gameJump, KEY_INTERACTION_TYPE::PRESS);

			p_inputs.restart = p_window.GetKey(restart, KEY_INTERACTION_TYPE::PRESS);

			p_inputs.showmenu = p_window.GetKey(gameMenu, KEY_INTERACTION_TYPE::PRESS);
			
			Wrapper::Window::Get()->closeGame = p_window.GetKey(gameQuit, KEY_INTERACTION_TYPE::PRESS);
		}
	}

	void InputManager::InputMouse(Inputs& p_inputs, const Wrapper::Window& p_window, const GAMESTATE p_gameState)
	{
		if (p_window.GetKey(KEY_TYPE::KEY_M, KEY_INTERACTION_TYPE::PRESS))
		{
			mouseCaptured = false;
		}

		//if (p_window.GetMouseButton(MOUSE_TYPE::KEY_MOUSE_BUTTON_LEFT, KEY_INTERACTION_TYPE::PRESS))
		//{
		//	p_inputs.attack = true;
		//}
		//else
		//{
		//	p_inputs.attack = false;
		//}

		if (p_window.GetMouseButton(MOUSE_TYPE::KEY_MOUSE_BUTTON_RIGHT, KEY_INTERACTION_TYPE::PRESS))
		{
			mouseCaptured = true;
			p_window.SetInputMode(true);
			timeMouseCaptured++;
		}
		else
		{
			mouseCaptured = false;
			timeMouseCaptured = 0;
			p_window.SetInputMode(false);
		}

		if (mouseCaptured)
		{
			Math::Vector2 cursorPosition = p_window.GetCursorPosition();
			mouseDeltaX = (float)(cursorPosition.x - mouseX);
			mouseDeltaY = (float)(cursorPosition.y - mouseY);
			mouseX = cursorPosition.x;
			mouseY = cursorPosition.y;

			if (timeMouseCaptured == 1) // firstFrame
			{
				p_inputs.deltaX = 0.f;
				p_inputs.deltaY = 0.f;
			}
			else
			{
				p_inputs.deltaX = mouseDeltaX;
				p_inputs.deltaY = mouseDeltaY;
			}
		}
		else
		{
			p_inputs.deltaX = 0.f;
			p_inputs.deltaY = 0.f;
		}

		p_inputs.sensitivity = sensitivity;
	}

	void InputManager::InputGamepad(Inputs& p_inputs, const Wrapper::Window& p_window, const GAMESTATE p_gameState)
	{
		if(p_window.GamepadPresent() == 0)
		{
			DefaultValueGamepad(p_inputs);
			return;
		}

		// --------
		//   Axis
		// --------
		int axesCount;
		const float* axes = p_window.GetJoystickAxes(&axesCount);
		float MIN = -0.07f;
		float MAX = 0.07f;

		if (axes[0] < MAX && axes[0] > MIN)
		{
			p_inputs.joystickLeftX = 0.f;
		}
		else
		{
			p_inputs.joystickLeftX = axes[0];
		}

		if (axes[1] < MAX && axes[1] > MIN)
		{
			p_inputs.joystickLeftY = 0.f;
		}
		else
		{
			p_inputs.joystickLeftY = axes[1];
		}

		if (axes[2] < MAX && axes[2] > MIN)
		{
			p_inputs.joystickRightX = 0.f;
		}
		else
		{
			p_inputs.joystickRightX = axes[2];
		}

		if (axes[3] < MAX && axes[3] > MIN)
		{
			p_inputs.joystickRightY = 0.f;
		}
		else
		{
			p_inputs.joystickRightY = axes[3];
		}

		if (axes[4] < MAX && axes[4] > MIN)
		{
			p_inputs.joystickLeftTrigger = 0.f;
		}
		else
		{
			p_inputs.joystickLeftTrigger = axes[4];
		}

		if (axes[5] < MAX && axes[5] > MIN)
		{
			p_inputs.joystickRightTrigger = 0.f;
		}
		else
		{
			p_inputs.joystickRightTrigger = axes[5];
		}

		// --------
		//  Button
		// --------
		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::A, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.gamepadA = true;
		}
		else
		{
			p_inputs.gamepadA = false;
		}

		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::B, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.gamepadB = true;
		}
		else
		{
			p_inputs.gamepadB = false;
		}

		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::X, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.gamepadX = true;
		}
		else
		{
			p_inputs.gamepadX = false;
		}

		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::Y, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.gamepadY = true;
		}
		else
		{
			p_inputs.gamepadY = false;
		}

		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::LEFT_BUTTON, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.gamepadLeftButton = true;
		}
		else
		{
			p_inputs.gamepadLeftButton = false;
		}

		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::RIGHT_BUTTON, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.gamepadRightButton = true;
		}
		else
		{
			p_inputs.gamepadRightButton = false;
		}

		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::DISPLAY_BUTTON, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.displayButton = true;
		}
		else
		{
			p_inputs.displayButton = false;
		}

		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::MENU_BUTTON, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.menuButton = true;
		}
		else
		{
			p_inputs.menuButton = false;
		}

		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::JOYSTICK_LEFT_BUTTON, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.joystickLeftButton = true;
		}
		else
		{
			p_inputs.joystickLeftButton = false;
		}

		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::JOYSTICK_RIGHT_BUTTON, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.joystickRightButton = true;
		}
		else
		{
			p_inputs.joystickRightButton = false;
		}

		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::MDB_DOWN, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.MDBDown = true;
		}
		else
		{
			p_inputs.MDBDown = false;
		}

		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::MDB_RIGHT, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.MDBRight = true;
		}
		else
		{
			p_inputs.MDBRight = false;
		}

		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::MDB_UP, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.MDBUp = true;
		}
		else
		{
			p_inputs.MDBUp = false;
		}

		if (p_window.GetJoystickButtons(JOYSTICK_BUTTON_TYPE::MDB_LEFT, KEY_INTERACTION_TYPE::PRESS))
		{
			p_inputs.MDBLeft = true;
		}
		else
		{
			p_inputs.MDBLeft = false;
		}
	}

	void InputManager::DefaultValueGamepad(Inputs& p_inputs)
	{
		p_inputs.joystickLeftX = 0.0f;
		p_inputs.joystickLeftY = 0.0f;
		p_inputs.joystickRightX = 0.0f;
		p_inputs.joystickRightY = 0.0f;
		p_inputs.joystickLeftTrigger = -1.0f;
		p_inputs.joystickRightTrigger = -1.0f;
		p_inputs.gamepadA = false;
		p_inputs.gamepadB = false;
		p_inputs.gamepadX = false;
		p_inputs.gamepadY = false;
		p_inputs.gamepadLeftButton = false;
		p_inputs.gamepadRightButton = false;
		p_inputs.displayButton = false;
		p_inputs.menuButton = false;
		p_inputs.joystickLeftButton = false;
		p_inputs.joystickRightButton = false;
		p_inputs.MDBDown = false;
		p_inputs.MDBRight = false;
		p_inputs.MDBUp = false;
		p_inputs.MDBLeft = false;
	}
}
