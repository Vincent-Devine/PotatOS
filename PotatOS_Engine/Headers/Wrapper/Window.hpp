#pragma once

#include <DLLInclude.hpp>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <Common.hpp>
#include <Math/Vector2.hpp>

namespace Wrapper
{
	class POTATOS_ENGINE_API Window
	{
	// Attributes
	public:
		GLFWwindow* window;
		Math::Vector2 windowSize;
		static int closeEditor;
		bool closeGame;

	private:
		static Window* singleton;
		std::string name;
		unsigned int width;
		unsigned int height;

	// Methods
	public:
		static Window* Get();

		void Create(const std::string& p_name, const unsigned int p_width, const unsigned int p_height);
		void Update();
		void Render();
		void Destroy();

		const bool WindowShouldClose() const;

		const bool GetKey(const KEY_TYPE& p_key, const KEY_INTERACTION_TYPE& p_keyInteraction) const;
		const bool GetMouseButton(const MOUSE_TYPE& p_key, const KEY_INTERACTION_TYPE& p_keyInteraction) const;
		void SetInputMode(const bool p_isDisabled) const;
		const Math::Vector2 GetCursorPosition() const;
		const Math::Vector2 GetCursorPositionInWindow() const;
		const int GamepadPresent() const;
		const float* GetJoystickAxes(int* p_axesCount) const;
		const bool GetJoystickButtons(const JOYSTICK_BUTTON_TYPE& p_key, const KEY_INTERACTION_TYPE& p_keyInteraction) const;

		const KEY_TYPE GetLastKeyboardKeyInput();
		const MOUSE_TYPE GetLastMouseKeyInput();
		const JOYSTICK_STICK_TYPE GetLastJoystickInput();
		const JOYSTICK_BUTTON_TYPE GetLastControllerInput();

		const KEY_TYPE GetKeyType(const int p_GLFWKey) const;
		const int GetGLFWKeyType(const KEY_TYPE p_keyType) const;
		const char* GetNameKeyType(const KEY_TYPE p_keyType) const;
		const char* GetNameKeyType(const MOUSE_TYPE p_keyType) const;
	};
}
