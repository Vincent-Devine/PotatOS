#include "pch.h"

#include <MonoBehavior/MoveCameraEditor.hpp>
#include <DebugSystem/Assertion.hpp>
#include <MonoBehavior/Renderer/Camera.hpp>

namespace MonoBehavior
{
	void MoveCameraEditor::Start(GAMESTATE* p_gameState)
	{
		componentType = SCRIPT;
		gameState = p_gameState;
		rotation = nullptr;
		for(unsigned int i = 0; i < gameObject->components.size(); i++)
		{
			MonoBehavior::Renderer::Camera* camera = nullptr;
			camera = dynamic_cast<MonoBehavior::Renderer::Camera*>(gameObject->components[i]);
			if (camera)
			{
				rotation = camera->GetPtrRotation();
				speed = camera->GetPtrSpeed();
				*speed = 35.f;
				return;
			}
		}
	}


	void MoveCameraEditor::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		Assertion(rotation, "No camera on this game object!");
		if (*gameState == GAMESTATE::PLAY)
		{
			return;
		}

		rotation->y -= p_inputs.deltaX * p_inputs.sensitivity;
		rotation->x -= p_inputs.deltaY * p_inputs.sensitivity;
		
		rotation->y -= p_inputs.joystickRightX;
		rotation->x -= p_inputs.joystickRightY;
		
		if (rotation->x < -90.f)
		{
			rotation->x = -90.f;
		}
		
		if (rotation->x > 90.f)
		{
			rotation->x = 90.f;
		}
		
		if (rotation->y < -360.f)
		{
			rotation->y = 360.f;
		}
		
		if (rotation->y > 360.f)
		{
			rotation->y = -360.f;
		}

		Math::Vector3 movement;
		bool modified = false;

		if (p_inputs.moveForward || p_inputs.joystickLeftY < 0.f)
		{
			movement += Math::Vector3(cosf(Math::DEG2RAD * (rotation->y + 90.f)), 0.f, -sinf(Math::DEG2RAD * (rotation->y + 90.f)));
			modified = true;
		}

		if (p_inputs.moveBackward || p_inputs.joystickLeftY > 0.f)
		{
			movement += Math::Vector3(-cosf(Math::DEG2RAD * (rotation->y + 90.f)), 0.f, sinf(Math::DEG2RAD * (rotation->y + 90.f)));
			modified = true;
		}

		if (p_inputs.moveRight || p_inputs.joystickLeftX > 0.f)
		{
			movement += Math::Vector3(cosf(Math::DEG2RAD * (rotation->y)), 0.f, -sinf(Math::DEG2RAD * (rotation->y)));
			modified = true;
		}

		if (p_inputs.moveLeft || p_inputs.joystickLeftX < 0.f)
		{
			movement += Math::Vector3(-cosf(Math::DEG2RAD * (rotation->y)), 0.f, sinf(Math::DEG2RAD * (rotation->y)));
			modified = true;
		}

		if (p_inputs.moveUp || p_inputs.joystickRightTrigger > -0.5f)
		{
			movement += Math::Vector3(0.f, 1.f, 0.f);
			modified = true;
		}

		if (p_inputs.moveDown || p_inputs.joystickLeftTrigger > -0.5f)
		{
			movement += Math::Vector3(0.f, -1.f, 0.f);
			modified = true;
		}

		if (modified)
		{
			gameObject->transform.SetPosition(gameObject->transform.GetLocalPosition() + Math::Vector3::Normalize(movement) * p_deltaTime * *speed);
		}
	}
}