#include "pch.h"

#include <Wrapper/Window.hpp>

#include <DebugSystem/Assertion.hpp>


#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_NATIVE_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

static void onError(int p_error, const char* p_description)
{
	Log::Print(p_description, LOG_LEVEL_TYPE::Critical);
}

int Wrapper::Window::closeEditor = GLFW_KEY_ESCAPE;

static void onInput(GLFWwindow* p_window, int p_key, int scancode, int p_action, int mods)
{
	if (p_key == Wrapper::Window::closeEditor && p_action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(p_window, GLFW_TRUE);
	}
}

namespace Wrapper
{
	Window* Window::singleton = nullptr;

	Window* Window::Get()
	{
		if (singleton == nullptr)
		{
			singleton = new Window();
		}
		return singleton;
	}

	void Window::Create(const std::string& p_name, const unsigned int p_width, const unsigned int p_height)
	{
		name = p_name;
		width = p_width;
		height = p_height;
		closeGame = false;

		glfwSetErrorCallback(onError);
		
		Assertion(glfwInit(), "GLFW could'nt init.");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

		if (!window)
		{
			glfwTerminate();
			Assertion(false, "GLFW could'nt create window.");
		}

		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, onInput);
	}

	void Window::Update()
	{
		glfwPollEvents();
		if (closeGame)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	}

	void Window::Render()
	{
		glfwSwapBuffers(window);
	}

	void Window::Destroy()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	const bool Window::WindowShouldClose() const
	{
		return glfwWindowShouldClose(window);
	}

	const bool Window::GetKey(const KEY_TYPE& p_key, const KEY_INTERACTION_TYPE& p_keyInteraction) const
	{
		int key = -1;
		int keyInteraction = -1;

		key = GetGLFWKeyType(p_key);

		switch (p_keyInteraction)
		{
		case KEY_INTERACTION_TYPE::RELEASE:
			keyInteraction = GLFW_RELEASE;
			break;

		case KEY_INTERACTION_TYPE::PRESS:
			keyInteraction = GLFW_PRESS;
			break;

		case KEY_INTERACTION_TYPE::REPEAT:
			keyInteraction = GLFW_REPEAT;
			break;

		default:
			Log::Print("Key Interaction not recognized.", LOG_LEVEL_TYPE::Warning);
			break;
		}

		if (p_key == KEY_TYPE::KEY_MOUSE_BUTTON_LEFT || p_key == KEY_TYPE::KEY_MOUSE_BUTTON_RIGHT)
		{
			return glfwGetMouseButton(window, key) == keyInteraction;
		}
		return glfwGetKey(window, key) == keyInteraction;
	}

	const bool Window::GetMouseButton(const MOUSE_TYPE& p_key, const KEY_INTERACTION_TYPE& p_keyInteraction) const
	{
		int mouse = 0;
		int keyInteraction = 0;

		switch (p_key)
		{
		case MOUSE_TYPE::KEY_MOUSE_BUTTON_RIGHT:
			mouse = GLFW_MOUSE_BUTTON_RIGHT;
			break;

		case MOUSE_TYPE::KEY_MOUSE_BUTTON_LEFT:
			mouse = GLFW_MOUSE_BUTTON_LEFT;
			break;

		default:
			Log::Print("Mouse key not recognized.", LOG_LEVEL_TYPE::Warning);
			break;
		}

		switch (p_keyInteraction)
		{
		case KEY_INTERACTION_TYPE::PRESS:
			keyInteraction = GLFW_PRESS;
			break;

		case KEY_INTERACTION_TYPE::RELEASE:
			keyInteraction = GLFW_RELEASE;
			break;

		case KEY_INTERACTION_TYPE::REPEAT:
			keyInteraction = GLFW_REPEAT;
			break;

		default:
			Log::Print("Key not recognized.", LOG_LEVEL_TYPE::Warning);
			break;
		}

		return glfwGetMouseButton(window, mouse) == keyInteraction;
	}

	void Window::SetInputMode(const bool p_isDisabled) const
	{
		if (p_isDisabled)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	const Math::Vector2 Window::GetCursorPosition() const
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		return Math::Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	}

	const Math::Vector2 Window::GetCursorPositionInWindow() const
	{
		POINT mousePos;
		GetCursorPos(&mousePos);

		HWND hDWND = glfwGetWin32Window(window);

		ScreenToClient(hDWND, &mousePos);
		return Math::Vector2(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	}

	const int Window::GamepadPresent() const
	{
		return glfwJoystickPresent(GLFW_JOYSTICK_1);
	}

	const float* Window::GetJoystickAxes(int* p_axesCount) const
	{
		return glfwGetJoystickAxes(GLFW_JOYSTICK_1, p_axesCount);
	}

	const bool Window::GetJoystickButtons(const JOYSTICK_BUTTON_TYPE& p_key, const KEY_INTERACTION_TYPE& p_keyInteraction) const
	{
		char key = ' ';
		int keyInteraction = -1;

		int buttonCount;
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

		switch (p_key)
		{
		case JOYSTICK_BUTTON_TYPE::A:
			key = buttons[0];
			break;

		case JOYSTICK_BUTTON_TYPE::B:
			key = buttons[1];
			break;

		case JOYSTICK_BUTTON_TYPE::X:
			key = buttons[2];
			break;

		case JOYSTICK_BUTTON_TYPE::Y:
			key = buttons[3];
			break;

		case JOYSTICK_BUTTON_TYPE::LEFT_BUTTON:
			key = buttons[4];
			break;

		case JOYSTICK_BUTTON_TYPE::RIGHT_BUTTON:
			key = buttons[5];
			break;

		case JOYSTICK_BUTTON_TYPE::DISPLAY_BUTTON:
			key = buttons[6];
			break;

		case JOYSTICK_BUTTON_TYPE::MENU_BUTTON:
			key = buttons[7];
			break;

		case JOYSTICK_BUTTON_TYPE::JOYSTICK_LEFT_BUTTON:
			key = buttons[8];
			break;

		case JOYSTICK_BUTTON_TYPE::JOYSTICK_RIGHT_BUTTON:
			key = buttons[9];
			break;

		case JOYSTICK_BUTTON_TYPE::MDB_UP:
			key = buttons[10];
			break;

		case JOYSTICK_BUTTON_TYPE::MDB_RIGHT:
			key = buttons[11];
			break;

		case JOYSTICK_BUTTON_TYPE::MDB_DOWN:
			key = buttons[12];
			break;

		case JOYSTICK_BUTTON_TYPE::MDB_LEFT:
			key = buttons[13];
			break;

		default:
			Log::Print("Mouse key not recognized.", LOG_LEVEL_TYPE::Warning);
			break;
		}

		switch (p_keyInteraction)
		{
		case KEY_INTERACTION_TYPE::PRESS:
			keyInteraction = GLFW_PRESS;
			break;

		case KEY_INTERACTION_TYPE::RELEASE:
			keyInteraction = GLFW_RELEASE;
			break;

		default:
			Log::Print("Key not recognized.", LOG_LEVEL_TYPE::Warning);
			break;
		}

		return key == keyInteraction;
	}

	const KEY_TYPE Window::GetLastKeyboardKeyInput()
	{
		for (unsigned int i = 32; i < GLFW_KEY_END; i++)
		{
			KEY_TYPE inputTest = static_cast<KEY_TYPE>(i);
			if (glfwGetKey(window, i) == GLFW_PRESS)
			{
				return GetKeyType(i);
			}
		}

		if (GetKey(KEY_TYPE::KEY_MOUSE_BUTTON_LEFT, KEY_INTERACTION_TYPE::PRESS))
		{
			return KEY_TYPE::KEY_MOUSE_BUTTON_LEFT;
		}
		else if (GetKey(KEY_TYPE::KEY_MOUSE_BUTTON_RIGHT, KEY_INTERACTION_TYPE::PRESS))
		{
			return KEY_TYPE::KEY_MOUSE_BUTTON_RIGHT;
		}

		return KEY_TYPE::KEY_UNKNOWN;
	}

	const MOUSE_TYPE Window::GetLastMouseKeyInput()
	{
		return MOUSE_TYPE::KEY_MOUSE_BUTTON_LEFT;
	}

	const JOYSTICK_STICK_TYPE Window::GetLastJoystickInput()
	{
		return JOYSTICK_STICK_TYPE::KEY_LEFT_STICK_X;
	}

	const JOYSTICK_BUTTON_TYPE Window::GetLastControllerInput()
	{
		return JOYSTICK_BUTTON_TYPE::A;
	}

	const KEY_TYPE Window::GetKeyType(const int p_GLFWKey) const
	{
		switch (p_GLFWKey)
		{
		case GLFW_KEY_W:
			return KEY_TYPE::KEY_W;

		case GLFW_KEY_S:
			return KEY_TYPE::KEY_S;

		case GLFW_KEY_A:
			return KEY_TYPE::KEY_A;

		case GLFW_KEY_D:
			return KEY_TYPE::KEY_D;

		case GLFW_KEY_LEFT_SHIFT:
			return KEY_TYPE::KEY_LEFT_SHIFT;

		case GLFW_KEY_SPACE:
			return KEY_TYPE::KEY_SPACE;

		case GLFW_KEY_M:
			return KEY_TYPE::KEY_M;

		case GLFW_KEY_P:
			return KEY_TYPE::KEY_P;

		case GLFW_KEY_R:
			return KEY_TYPE::KEY_R;

		case GLFW_KEY_F:
			return KEY_TYPE::KEY_F;

		case GLFW_KEY_LEFT_CONTROL:
			return KEY_TYPE::KEY_LEFT_CONTROL;

		case GLFW_KEY_RIGHT_CONTROL:
			return KEY_TYPE::KEY_RIGHT_CONTROL;

		case GLFW_KEY_APOSTROPHE:
			return KEY_TYPE::KEY_APOSTROPHE;

		case GLFW_KEY_COMMA:
			return KEY_TYPE::KEY_COMMA;

		case GLFW_KEY_MINUS:
			return KEY_TYPE::KEY_MINUS;

		case GLFW_KEY_PERIOD:
			return KEY_TYPE::KEY_PERIOD;

		case GLFW_KEY_SLASH:
			return KEY_TYPE::KEY_SLASH;

		case GLFW_KEY_0:
			return KEY_TYPE::KEY_0;

		case GLFW_KEY_1:
			return KEY_TYPE::KEY_1;

		case GLFW_KEY_2:
			return KEY_TYPE::KEY_2;
		case GLFW_KEY_3:
			return KEY_TYPE::KEY_3;

		case GLFW_KEY_4:
			return KEY_TYPE::KEY_4;

		case GLFW_KEY_5:
			return KEY_TYPE::KEY_5;

		case GLFW_KEY_6:
			return KEY_TYPE::KEY_6;

		case GLFW_KEY_7:
			return KEY_TYPE::KEY_7;

		case GLFW_KEY_8:
			return KEY_TYPE::KEY_8;

		case GLFW_KEY_9:
			return KEY_TYPE::KEY_9;

		case GLFW_KEY_SEMICOLON:
			return KEY_TYPE::KEY_SEMICOLON;

		case GLFW_KEY_EQUAL:
			return KEY_TYPE::KEY_EQUAL;

		case GLFW_KEY_B:
			return KEY_TYPE::KEY_B;

		case GLFW_KEY_C:
			return KEY_TYPE::KEY_C;

		case GLFW_KEY_E:
			return KEY_TYPE::KEY_E;

		case GLFW_KEY_G:
			return KEY_TYPE::KEY_G;

		case GLFW_KEY_H:
			return KEY_TYPE::KEY_H;

		case GLFW_KEY_I:
			return KEY_TYPE::KEY_I;

		case GLFW_KEY_J:
			return KEY_TYPE::KEY_J;

		case GLFW_KEY_K:
			return KEY_TYPE::KEY_K;

		case GLFW_KEY_L:
			return KEY_TYPE::KEY_L;

		case GLFW_KEY_N:
			return KEY_TYPE::KEY_N;

		case GLFW_KEY_O:
			return KEY_TYPE::KEY_O;

		case GLFW_KEY_Q:
			return KEY_TYPE::KEY_Q;

		case GLFW_KEY_T:
			return KEY_TYPE::KEY_T;

		case GLFW_KEY_U:
			return KEY_TYPE::KEY_U;

		case GLFW_KEY_V:
			return KEY_TYPE::KEY_V;

		case GLFW_KEY_X:
			return KEY_TYPE::KEY_X;

		case GLFW_KEY_Y:
			return KEY_TYPE::KEY_Y;

		case GLFW_KEY_Z:
			return KEY_TYPE::KEY_Z;

		case GLFW_KEY_LEFT_BRACKET:
			return KEY_TYPE::KEY_LEFT_BRACKET;

		case GLFW_KEY_BACKSLASH:
			return KEY_TYPE::KEY_BACKSLASH;

		case GLFW_KEY_RIGHT_BRACKET:
			return KEY_TYPE::KEY_RIGHT_BRACKET;

		case GLFW_KEY_GRAVE_ACCENT:
			return KEY_TYPE::KEY_GRAVE_ACCENT;

		case GLFW_KEY_WORLD_1:
			return KEY_TYPE::KEY_WORLD_1;

		case GLFW_KEY_WORLD_2:
			return KEY_TYPE::KEY_WORLD_2;

		case GLFW_KEY_ESCAPE:
			return KEY_TYPE::KEY_ESCAPE;

		case GLFW_KEY_ENTER:
			return KEY_TYPE::KEY_ENTER;

		case GLFW_KEY_TAB:
			return KEY_TYPE::KEY_TAB;

		case GLFW_KEY_BACKSPACE:
			return KEY_TYPE::KEY_BACKSPACE;

		case GLFW_KEY_INSERT:
			return KEY_TYPE::KEY_INSERT;

		case GLFW_KEY_DELETE:
			return KEY_TYPE::KEY_DELETE;

		case GLFW_KEY_RIGHT:
			return KEY_TYPE::KEY_RIGHT;

		case GLFW_KEY_LEFT:
			return KEY_TYPE::KEY_LEFT;

		case GLFW_KEY_DOWN:
			return KEY_TYPE::KEY_DOWN;

		case GLFW_KEY_UP:
			return KEY_TYPE::KEY_UP;

		case GLFW_KEY_PAGE_UP:
			return KEY_TYPE::KEY_PAGE_UP;

		case GLFW_KEY_PAGE_DOWN:
			return KEY_TYPE::KEY_PAGE_DOWN;

		case GLFW_KEY_HOME:
			return KEY_TYPE::KEY_HOME;

		case GLFW_KEY_END:
			return KEY_TYPE::KEY_END;

		case GLFW_KEY_CAPS_LOCK:
			return KEY_TYPE::KEY_CAPS_LOCK;

		case GLFW_KEY_SCROLL_LOCK:
			return KEY_TYPE::KEY_SCROLL_LOCK;

		case GLFW_KEY_NUM_LOCK:
			return KEY_TYPE::KEY_NUM_LOCK;

		case GLFW_KEY_PRINT_SCREEN:
			return KEY_TYPE::KEY_PRINT_SCREEN;

		case GLFW_KEY_PAUSE:
			return KEY_TYPE::KEY_PAUSE;

		case GLFW_KEY_F1:
			return KEY_TYPE::KEY_F1;

		case GLFW_KEY_F2:
			return KEY_TYPE::KEY_F2;

		case GLFW_KEY_F3:
			return KEY_TYPE::KEY_F3;

		case GLFW_KEY_F4:
			return KEY_TYPE::KEY_F4;

		case GLFW_KEY_F5:
			return KEY_TYPE::KEY_F5;

		case GLFW_KEY_F6:
			return KEY_TYPE::KEY_F6;

		case GLFW_KEY_F7:
			return KEY_TYPE::KEY_F7;

		case GLFW_KEY_F8:
			return KEY_TYPE::KEY_F8;

		case GLFW_KEY_F9:
			return KEY_TYPE::KEY_F9;

		case GLFW_KEY_F10:
			return KEY_TYPE::KEY_F10;

		case GLFW_KEY_F11:
			return KEY_TYPE::KEY_F11;

		case GLFW_KEY_F12:
			return KEY_TYPE::KEY_F12;

		case GLFW_KEY_F13:
			return KEY_TYPE::KEY_F13;

		case GLFW_KEY_F14:
			return KEY_TYPE::KEY_F14;

		case GLFW_KEY_F15:
			return KEY_TYPE::KEY_F15;

		case GLFW_KEY_F16:
			return KEY_TYPE::KEY_F16;

		case GLFW_KEY_F17:
			return KEY_TYPE::KEY_F17;

		case GLFW_KEY_F18:
			return KEY_TYPE::KEY_F18;

		case GLFW_KEY_F19:
			return KEY_TYPE::KEY_F19;

		case GLFW_KEY_F20:
			return KEY_TYPE::KEY_F20;

		case GLFW_KEY_F21:
			return KEY_TYPE::KEY_F21;

		case GLFW_KEY_F22:
			return KEY_TYPE::KEY_F22;

		case GLFW_KEY_F23:
			return KEY_TYPE::KEY_F23;

		case GLFW_KEY_F24:
			return KEY_TYPE::KEY_F24;

		case GLFW_KEY_F25:
			return KEY_TYPE::KEY_F25;

		case GLFW_KEY_KP_0:
			return KEY_TYPE::KEY_KP_0;

		case GLFW_KEY_KP_1:
			return KEY_TYPE::KEY_KP_1;

		case GLFW_KEY_KP_2:
			return KEY_TYPE::KEY_KP_2;

		case GLFW_KEY_KP_3:
			return KEY_TYPE::KEY_KP_3;

		case GLFW_KEY_KP_4:
			return KEY_TYPE::KEY_KP_4;

		case GLFW_KEY_KP_5:
			return KEY_TYPE::KEY_KP_5;

		case GLFW_KEY_KP_6:
			return KEY_TYPE::KEY_KP_6;

		case GLFW_KEY_KP_7:
			return KEY_TYPE::KEY_KP_7;

		case GLFW_KEY_KP_8:
			return KEY_TYPE::KEY_KP_8;

		case GLFW_KEY_KP_9:
			return KEY_TYPE::KEY_KP_9;

		case GLFW_KEY_KP_DECIMAL:
			return KEY_TYPE::KEY_KP_DECIMAL;

		case GLFW_KEY_KP_DIVIDE:
			return KEY_TYPE::KEY_KP_DIVIDE;

		case GLFW_KEY_KP_MULTIPLY:
			return KEY_TYPE::KEY_KP_MULTIPLY;

		case GLFW_KEY_KP_SUBTRACT:
			return KEY_TYPE::KEY_KP_SUBTRACT;

		case GLFW_KEY_KP_ADD:
			return KEY_TYPE::KEY_KP_ADD;

		case GLFW_KEY_KP_ENTER:
			return KEY_TYPE::KEY_KP_ENTER;

		case GLFW_KEY_KP_EQUAL:
			return KEY_TYPE::KEY_KP_EQUAL;

		case GLFW_KEY_LEFT_ALT:
			return KEY_TYPE::KEY_LEFT_ALT;

		case GLFW_KEY_LEFT_SUPER:
			return KEY_TYPE::KEY_LEFT_SUPER;

		case GLFW_KEY_RIGHT_SHIFT:
			return KEY_TYPE::KEY_RIGHT_SHIFT;

		case GLFW_KEY_RIGHT_ALT:
			return KEY_TYPE::KEY_RIGHT_ALT;

		case GLFW_KEY_RIGHT_SUPER:
			return KEY_TYPE::KEY_RIGHT_SUPER;

		case GLFW_KEY_MENU:
			return KEY_TYPE::KEY_MENU;
			
		case GLFW_MOUSE_BUTTON_RIGHT:
			return KEY_TYPE::KEY_MOUSE_BUTTON_RIGHT;
			
		case GLFW_MOUSE_BUTTON_LEFT:
			return KEY_TYPE::KEY_MOUSE_BUTTON_LEFT;

		default:
			return KEY_TYPE::KEY_UNKNOWN;
		}
	}

	const int Window::GetGLFWKeyType(const KEY_TYPE p_keyType) const
	{
		switch (p_keyType)
		{
		case KEY_TYPE::KEY_W:
			return GLFW_KEY_W;

		case KEY_TYPE::KEY_S:
			return GLFW_KEY_S;

		case KEY_TYPE::KEY_A:
			return GLFW_KEY_A;

		case KEY_TYPE::KEY_D:
			return GLFW_KEY_D;

		case KEY_TYPE::KEY_LEFT_SHIFT:
			return GLFW_KEY_LEFT_SHIFT;

		case KEY_TYPE::KEY_SPACE:
			return GLFW_KEY_SPACE;

		case KEY_TYPE::KEY_M:
			return GLFW_KEY_M;

		case KEY_TYPE::KEY_P:
			return GLFW_KEY_P;

		case KEY_TYPE::KEY_R:
			return GLFW_KEY_R;

		case KEY_TYPE::KEY_F:
			return GLFW_KEY_F;

		case KEY_TYPE::KEY_LEFT_CONTROL:
			return GLFW_KEY_LEFT_CONTROL;

		case KEY_TYPE::KEY_RIGHT_CONTROL:
			return GLFW_KEY_RIGHT_CONTROL;

		case KEY_TYPE::KEY_APOSTROPHE:
			return GLFW_KEY_APOSTROPHE;

		case KEY_TYPE::KEY_COMMA:
			return GLFW_KEY_COMMA;

		case KEY_TYPE::KEY_MINUS:
			return GLFW_KEY_MINUS;

		case KEY_TYPE::KEY_PERIOD:
			return GLFW_KEY_PERIOD;

		case KEY_TYPE::KEY_SLASH:
			return GLFW_KEY_SLASH;

		case KEY_TYPE::KEY_0:
			return GLFW_KEY_0;

		case KEY_TYPE::KEY_1:
			return GLFW_KEY_1;

		case KEY_TYPE::KEY_2:
			return GLFW_KEY_2;
		case KEY_TYPE::KEY_3:
			return GLFW_KEY_3;

		case KEY_TYPE::KEY_4:
			return GLFW_KEY_4;

		case KEY_TYPE::KEY_5:
			return GLFW_KEY_5;

		case KEY_TYPE::KEY_6:
			return GLFW_KEY_6;

		case KEY_TYPE::KEY_7:
			return GLFW_KEY_7;

		case KEY_TYPE::KEY_8:
			return GLFW_KEY_8;

		case KEY_TYPE::KEY_9:
			return GLFW_KEY_9;

		case KEY_TYPE::KEY_SEMICOLON:
			return GLFW_KEY_SEMICOLON;

		case KEY_TYPE::KEY_EQUAL:
			return GLFW_KEY_EQUAL;

		case KEY_TYPE::KEY_B:
			return GLFW_KEY_B;

		case KEY_TYPE::KEY_C:
			return GLFW_KEY_C;

		case KEY_TYPE::KEY_E:
			return GLFW_KEY_E;

		case KEY_TYPE::KEY_G:
			return GLFW_KEY_G;

		case KEY_TYPE::KEY_H:
			return GLFW_KEY_H;

		case KEY_TYPE::KEY_I:
			return GLFW_KEY_I;

		case KEY_TYPE::KEY_J:
			return GLFW_KEY_J;

		case KEY_TYPE::KEY_K:
			return GLFW_KEY_K;

		case KEY_TYPE::KEY_L:
			return GLFW_KEY_L;

		case KEY_TYPE::KEY_N:
			return GLFW_KEY_N;

		case KEY_TYPE::KEY_O:
			return GLFW_KEY_O;

		case KEY_TYPE::KEY_Q:
			return GLFW_KEY_Q;

		case KEY_TYPE::KEY_T:
			return GLFW_KEY_T;

		case KEY_TYPE::KEY_U:
			return GLFW_KEY_U;

		case KEY_TYPE::KEY_V:
			return GLFW_KEY_V;

		case KEY_TYPE::KEY_X:
			return GLFW_KEY_X;

		case KEY_TYPE::KEY_Y:
			return GLFW_KEY_Y;

		case KEY_TYPE::KEY_Z:
			return GLFW_KEY_Z;

		case KEY_TYPE::KEY_LEFT_BRACKET:
			return GLFW_KEY_LEFT_BRACKET;

		case KEY_TYPE::KEY_BACKSLASH:
			return GLFW_KEY_BACKSLASH;

		case KEY_TYPE::KEY_RIGHT_BRACKET:
			return GLFW_KEY_RIGHT_BRACKET;

		case KEY_TYPE::KEY_GRAVE_ACCENT:
			return GLFW_KEY_GRAVE_ACCENT;

		case KEY_TYPE::KEY_WORLD_1:
			return GLFW_KEY_WORLD_1;

		case KEY_TYPE::KEY_WORLD_2:
			return GLFW_KEY_WORLD_2;

		case KEY_TYPE::KEY_ESCAPE:
			return GLFW_KEY_ESCAPE;

		case KEY_TYPE::KEY_ENTER:
			return GLFW_KEY_ENTER;

		case KEY_TYPE::KEY_TAB:
			return GLFW_KEY_TAB;

		case KEY_TYPE::KEY_BACKSPACE:
			return GLFW_KEY_BACKSPACE;

		case KEY_TYPE::KEY_INSERT:
			return GLFW_KEY_INSERT;

		case KEY_TYPE::KEY_DELETE:
			return GLFW_KEY_DELETE;

		case KEY_TYPE::KEY_RIGHT:
			return GLFW_KEY_RIGHT;

		case KEY_TYPE::KEY_LEFT:
			return GLFW_KEY_LEFT;

		case KEY_TYPE::KEY_DOWN:
			return GLFW_KEY_DOWN;

		case KEY_TYPE::KEY_UP:
			return GLFW_KEY_UP;

		case KEY_TYPE::KEY_PAGE_UP:
			return GLFW_KEY_PAGE_UP;

		case KEY_TYPE::KEY_PAGE_DOWN:
			return GLFW_KEY_PAGE_DOWN;

		case KEY_TYPE::KEY_HOME:
			return GLFW_KEY_HOME;

		case KEY_TYPE::KEY_END:
			return GLFW_KEY_END;

		case KEY_TYPE::KEY_CAPS_LOCK:
			return GLFW_KEY_CAPS_LOCK;

		case KEY_TYPE::KEY_SCROLL_LOCK:
			return GLFW_KEY_SCROLL_LOCK;

		case KEY_TYPE::KEY_NUM_LOCK:
			return GLFW_KEY_NUM_LOCK;

		case KEY_TYPE::KEY_PRINT_SCREEN:
			return GLFW_KEY_PRINT_SCREEN;

		case KEY_TYPE::KEY_PAUSE:
			return GLFW_KEY_PAUSE;

		case KEY_TYPE::KEY_F1:
			return GLFW_KEY_F1;

		case KEY_TYPE::KEY_F2:
			return GLFW_KEY_F2;

		case KEY_TYPE::KEY_F3:
			return GLFW_KEY_F3;

		case KEY_TYPE::KEY_F4:
			return GLFW_KEY_F4;

		case KEY_TYPE::KEY_F5:
			return GLFW_KEY_F5;

		case KEY_TYPE::KEY_F6:
			return GLFW_KEY_F6;

		case KEY_TYPE::KEY_F7:
			return GLFW_KEY_F7;

		case KEY_TYPE::KEY_F8:
			return GLFW_KEY_F8;

		case KEY_TYPE::KEY_F9:
			return GLFW_KEY_F9;

		case KEY_TYPE::KEY_F10:
			return GLFW_KEY_F10;

		case KEY_TYPE::KEY_F11:
			return GLFW_KEY_F11;

		case KEY_TYPE::KEY_F12:
			return GLFW_KEY_F12;

		case KEY_TYPE::KEY_F13:
			return GLFW_KEY_F13;

		case KEY_TYPE::KEY_F14:
			return GLFW_KEY_F14;

		case KEY_TYPE::KEY_F15:
			return GLFW_KEY_F15;

		case KEY_TYPE::KEY_F16:
			return GLFW_KEY_F16;

		case KEY_TYPE::KEY_F17:
			return GLFW_KEY_F17;

		case KEY_TYPE::KEY_F18:
			return GLFW_KEY_F18;

		case KEY_TYPE::KEY_F19:
			return GLFW_KEY_F19;

		case KEY_TYPE::KEY_F20:
			return GLFW_KEY_F20;

		case KEY_TYPE::KEY_F21:
			return GLFW_KEY_F21;

		case KEY_TYPE::KEY_F22:
			return GLFW_KEY_F22;

		case KEY_TYPE::KEY_F23:
			return GLFW_KEY_F23;

		case KEY_TYPE::KEY_F24:
			return GLFW_KEY_F24;

		case KEY_TYPE::KEY_F25:
			return GLFW_KEY_F25;

		case KEY_TYPE::KEY_KP_0:
			return GLFW_KEY_KP_0;

		case KEY_TYPE::KEY_KP_1:
			return GLFW_KEY_KP_1;

		case KEY_TYPE::KEY_KP_2:
			return GLFW_KEY_KP_2;

		case KEY_TYPE::KEY_KP_3:
			return GLFW_KEY_KP_3;

		case KEY_TYPE::KEY_KP_4:
			return GLFW_KEY_KP_4;

		case KEY_TYPE::KEY_KP_5:
			return GLFW_KEY_KP_5;

		case KEY_TYPE::KEY_KP_6:
			return GLFW_KEY_KP_6;

		case KEY_TYPE::KEY_KP_7:
			return GLFW_KEY_KP_7;

		case KEY_TYPE::KEY_KP_8:
			return GLFW_KEY_KP_8;

		case KEY_TYPE::KEY_KP_9:
			return GLFW_KEY_KP_9;

		case KEY_TYPE::KEY_KP_DECIMAL:
			return GLFW_KEY_KP_DECIMAL;

		case KEY_TYPE::KEY_KP_DIVIDE:
			return GLFW_KEY_KP_DIVIDE;

		case KEY_TYPE::KEY_KP_MULTIPLY:
			return GLFW_KEY_KP_MULTIPLY;

		case KEY_TYPE::KEY_KP_SUBTRACT:
			return GLFW_KEY_KP_SUBTRACT;

		case KEY_TYPE::KEY_KP_ADD:
			return GLFW_KEY_KP_ADD;

		case KEY_TYPE::KEY_KP_ENTER:
			return GLFW_KEY_KP_ENTER;

		case KEY_TYPE::KEY_KP_EQUAL:
			return GLFW_KEY_KP_EQUAL;

		case KEY_TYPE::KEY_LEFT_ALT:
			return GLFW_KEY_LEFT_ALT;

		case KEY_TYPE::KEY_LEFT_SUPER:
			return GLFW_KEY_LEFT_SUPER;

		case KEY_TYPE::KEY_RIGHT_SHIFT:
			return GLFW_KEY_RIGHT_SHIFT;

		case KEY_TYPE::KEY_RIGHT_ALT:
			return GLFW_KEY_RIGHT_ALT;

		case KEY_TYPE::KEY_RIGHT_SUPER:
			return GLFW_KEY_RIGHT_SUPER;

		case KEY_TYPE::KEY_MENU:
			return GLFW_KEY_MENU;

		case KEY_TYPE::KEY_MOUSE_BUTTON_RIGHT:
			return GLFW_MOUSE_BUTTON_RIGHT;

		case KEY_TYPE::KEY_MOUSE_BUTTON_LEFT:
			return GLFW_MOUSE_BUTTON_LEFT;

		default:
			return GLFW_KEY_UNKNOWN;
		}
	}

	const char* Window::GetNameKeyType(const KEY_TYPE p_keyType) const
	{
		switch (p_keyType)
		{
		case KEY_TYPE::KEY_W:
			return "W";

		case KEY_TYPE::KEY_S:
			return "S";

		case KEY_TYPE::KEY_A:
			return "A";

		case KEY_TYPE::KEY_D:
			return "D";

		case KEY_TYPE::KEY_LEFT_SHIFT:
			return "LEFT_SHIFT";

		case KEY_TYPE::KEY_SPACE:
			return "SPACE";

		case KEY_TYPE::KEY_M:
			return "M";

		case KEY_TYPE::KEY_P:
			return "P";

		case KEY_TYPE::KEY_R:
			return "R";

		case KEY_TYPE::KEY_F:
			return "F";

		case KEY_TYPE::KEY_LEFT_CONTROL:
			return "LEFT_CONTROL";

		case KEY_TYPE::KEY_RIGHT_CONTROL:
			return "RIGHT_CONTROL";

		case KEY_TYPE::KEY_APOSTROPHE:
			return "APOSTROPHE";

		case KEY_TYPE::KEY_COMMA:
			return "COMMA";

		case KEY_TYPE::KEY_MINUS:
			return "MINUS";

		case KEY_TYPE::KEY_PERIOD:
			return "PERIOD";

		case KEY_TYPE::KEY_SLASH:
			return "SLASH";

		case KEY_TYPE::KEY_0:
			return "0";

		case KEY_TYPE::KEY_1:
			return "1";

		case KEY_TYPE::KEY_2:
			return "2";
		case KEY_TYPE::KEY_3:
			return "3";

		case KEY_TYPE::KEY_4:
			return "4";

		case KEY_TYPE::KEY_5:
			return "5";

		case KEY_TYPE::KEY_6:
			return "6";

		case KEY_TYPE::KEY_7:
			return "7";

		case KEY_TYPE::KEY_8:
			return "8";

		case KEY_TYPE::KEY_9:
			return "9";

		case KEY_TYPE::KEY_SEMICOLON:
			return "SEMICOLON";

		case KEY_TYPE::KEY_EQUAL:
			return "EQUAL";

		case KEY_TYPE::KEY_B:
			return "B";

		case KEY_TYPE::KEY_C:
			return "C";

		case KEY_TYPE::KEY_E:
			return "E";

		case KEY_TYPE::KEY_G:
			return "G";

		case KEY_TYPE::KEY_H:
			return "H";

		case KEY_TYPE::KEY_I:
			return "I";

		case KEY_TYPE::KEY_J:
			return "J";

		case KEY_TYPE::KEY_K:
			return "K";

		case KEY_TYPE::KEY_L:
			return "L";

		case KEY_TYPE::KEY_N:
			return "N";

		case KEY_TYPE::KEY_O:
			return "O";

		case KEY_TYPE::KEY_Q:
			return "Q";

		case KEY_TYPE::KEY_T:
			return "T";

		case KEY_TYPE::KEY_U:
			return "U";

		case KEY_TYPE::KEY_V:
			return "V";

		case KEY_TYPE::KEY_X:
			return "X";

		case KEY_TYPE::KEY_Y:
			return "Y";

		case KEY_TYPE::KEY_Z:
			return "Z";

		case KEY_TYPE::KEY_LEFT_BRACKET:
			return "LEFT_BRACKET";

		case KEY_TYPE::KEY_BACKSLASH:
			return "BACKSLASH";

		case KEY_TYPE::KEY_RIGHT_BRACKET:
			return "RIGHT_BRACKET";

		case KEY_TYPE::KEY_GRAVE_ACCENT:
			return "GRAVE_ACCENT";

		case KEY_TYPE::KEY_WORLD_1:
			return "WORLD_1";

		case KEY_TYPE::KEY_WORLD_2:
			return "WORLD_2";

		case KEY_TYPE::KEY_ESCAPE:
			return "ESCAPE";

		case KEY_TYPE::KEY_ENTER:
			return "ENTER";

		case KEY_TYPE::KEY_TAB:
			return "TAB";

		case KEY_TYPE::KEY_BACKSPACE:
			return "BACKSPACE";

		case KEY_TYPE::KEY_INSERT:
			return "INSERT";

		case KEY_TYPE::KEY_DELETE:
			return "DELETE";

		case KEY_TYPE::KEY_RIGHT:
			return "RIGHT";

		case KEY_TYPE::KEY_LEFT:
			return "LEFT";

		case KEY_TYPE::KEY_DOWN:
			return "DOWN";

		case KEY_TYPE::KEY_UP:
			return "UP";

		case KEY_TYPE::KEY_PAGE_UP:
			return "PAGE_UP";

		case KEY_TYPE::KEY_PAGE_DOWN:
			return "PAGE_DOWN";

		case KEY_TYPE::KEY_HOME:
			return "HOME";

		case KEY_TYPE::KEY_END:
			return "END";

		case KEY_TYPE::KEY_CAPS_LOCK:
			return "CAPS_LOCK";

		case KEY_TYPE::KEY_SCROLL_LOCK:
			return "SCROLL_LOCK";

		case KEY_TYPE::KEY_NUM_LOCK:
			return "NUM_LOCK";

		case KEY_TYPE::KEY_PRINT_SCREEN:
			return "PRINT_SCREEN";

		case KEY_TYPE::KEY_PAUSE:
			return "PAUSE";

		case KEY_TYPE::KEY_F1:
			return "F1";

		case KEY_TYPE::KEY_F2:
			return "F2";

		case KEY_TYPE::KEY_F3:
			return "F3";

		case KEY_TYPE::KEY_F4:
			return "F4";

		case KEY_TYPE::KEY_F5:
			return "F5";

		case KEY_TYPE::KEY_F6:
			return "F6";

		case KEY_TYPE::KEY_F7:
			return "F7";

		case KEY_TYPE::KEY_F8:
			return "F8";

		case KEY_TYPE::KEY_F9:
			return "F9";

		case KEY_TYPE::KEY_F10:
			return "F10";

		case KEY_TYPE::KEY_F11:
			return "F11";

		case KEY_TYPE::KEY_F12:
			return "F12";

		case KEY_TYPE::KEY_F13:
			return "F13";

		case KEY_TYPE::KEY_F14:
			return "F14";

		case KEY_TYPE::KEY_F15:
			return "F15";

		case KEY_TYPE::KEY_F16:
			return "F16";

		case KEY_TYPE::KEY_F17:
			return "F17";

		case KEY_TYPE::KEY_F18:
			return "F18";

		case KEY_TYPE::KEY_F19:
			return "F19";

		case KEY_TYPE::KEY_F20:
			return "F20";

		case KEY_TYPE::KEY_F21:
			return "F21";

		case KEY_TYPE::KEY_F22:
			return "F22";

		case KEY_TYPE::KEY_F23:
			return "F23";

		case KEY_TYPE::KEY_F24:
			return "F24";

		case KEY_TYPE::KEY_F25:
			return "F25";

		case KEY_TYPE::KEY_KP_0:
			return "KP_0";

		case KEY_TYPE::KEY_KP_1:
			return "KP_1";

		case KEY_TYPE::KEY_KP_2:
			return "KP_2";

		case KEY_TYPE::KEY_KP_3:
			return "KP_3";

		case KEY_TYPE::KEY_KP_4:
			return "KP_4";

		case KEY_TYPE::KEY_KP_5:
			return "KP_5";

		case KEY_TYPE::KEY_KP_6:
			return "KP_6";

		case KEY_TYPE::KEY_KP_7:
			return "KP_7";

		case KEY_TYPE::KEY_KP_8:
			return "KP_8";

		case KEY_TYPE::KEY_KP_9:
			return "KP_9";

		case KEY_TYPE::KEY_KP_DECIMAL:
			return "KP_DECIMAL";

		case KEY_TYPE::KEY_KP_DIVIDE:
			return "KP_DIVIDE";

		case KEY_TYPE::KEY_KP_MULTIPLY:
			return "KP_MULTIPLY";

		case KEY_TYPE::KEY_KP_SUBTRACT:
			return "KP_SUBTRACT";

		case KEY_TYPE::KEY_KP_ADD:
			return "KP_ADD";

		case KEY_TYPE::KEY_KP_ENTER:
			return "KP_ENTER";

		case KEY_TYPE::KEY_KP_EQUAL:
			return "KP_EQUAL";

		case KEY_TYPE::KEY_LEFT_ALT:
			return "LEFT_ALT";

		case KEY_TYPE::KEY_LEFT_SUPER:
			return "LEFT_SUPER";

		case KEY_TYPE::KEY_RIGHT_SHIFT:
			return "RIGHT_SHIFT";

		case KEY_TYPE::KEY_RIGHT_ALT:
			return "RIGHT_ALT";

		case KEY_TYPE::KEY_RIGHT_SUPER:
			return "RIGHT_SUPER";

		case KEY_TYPE::KEY_MENU:
			return "MENU";

		case KEY_TYPE::KEY_MOUSE_BUTTON_RIGHT:
			return "MOUSE_BUTTON_RIGHT";

		case KEY_TYPE::KEY_MOUSE_BUTTON_LEFT:
			return "MOUSE_BUTTON_LEFT";

		default:
			return "UNKNOWN";
		}
	}

	const char* Window::GetNameKeyType(const MOUSE_TYPE p_keyType) const
	{
		if (p_keyType == MOUSE_TYPE::KEY_MOUSE_BUTTON_RIGHT)
		{
			return "Right mouse click";
		}
		else
		{
			return "Left mouse click";
		}
	}
}