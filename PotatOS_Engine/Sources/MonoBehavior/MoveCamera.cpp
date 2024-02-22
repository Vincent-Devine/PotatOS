#include "pch.h"

#include <MonoBehavior/MoveCamera.hpp>
#include <MonoBehavior/Renderer/Camera.hpp>
#include <MonoBehavior/Physics/Collider.hpp>

namespace MonoBehavior
{
	void MoveCamera::Start(GAMESTATE* p_gameState)
	{
		componentType = SCRIPT;
		gameState = p_gameState;
		MOVE_SPEED = 10.f;
		for (unsigned int i = 0; i < gameObject->components.size(); i++)
		{
			MonoBehavior::Renderer::Camera* camera = nullptr;
			camera = dynamic_cast<MonoBehavior::Renderer::Camera*>(gameObject->components[i]);
			if (camera)
			{
				startingRotation = desiredRotation = gameObject->transform.GetLocalRotation();
				speed = camera->GetPtrSpeed();
				*speed = MOVE_SPEED;
				totalSlerpTime = 1.f;
				curTime = totalSlerpTime + 1.f;
				return;
			}
		}
		
	}

	void MoveCamera::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (*gameState == GAMESTATE::EDIT || !PtrCheck() || !lifeScript->IsAlive())
		{
			return;
		}

		Math::Vector3 movement;
		bool modified = false;

		if (p_inputs.moveForward || p_inputs.joystickLeftY < 0.f)
		{
			movement += Math::Vector3(cosf(Math::DEG2RAD * 65.0f), 0.f, -sinf(Math::DEG2RAD * 65.0f));
			modified = true;
		}

		if (p_inputs.moveBackward || p_inputs.joystickLeftY > 0.f)
		{
			movement += Math::Vector3(-cosf(Math::DEG2RAD * 65.0f), 0.f, sinf(Math::DEG2RAD * 65.0f));
			modified = true;
		}

		if (p_inputs.moveRight || p_inputs.joystickLeftX > 0.f)
		{
			movement += Math::Vector3(cosf(Math::DEG2RAD * -25.f), 0.f, -sinf(Math::DEG2RAD * -25.f));
			modified = true;
		}

		if (p_inputs.moveLeft || p_inputs.joystickLeftX < 0.f)
		{
			movement += Math::Vector3(-cosf(Math::DEG2RAD * -25.f), 0.f, sinf(Math::DEG2RAD * -25.f));
			modified = true;
		}

		if (modified)
		{
			if (Math::Vector3::Magnitude(movement) == 0.f || !gameObject->transform.parentTransform)
			{
				return;
			}

			if (playerAttack && playerAttack->GetIsAttacking())
			{
				*speed = playerAttack->GetSpeedInAttack();
			}
			else
			{
				*speed = MOVE_SPEED;
			}

			DataStructure::Transform* transform = gameObject->transform.parentTransform;

			transform->SetPosition(transform->GetLocalPosition() + Math::Vector3::Normalize(movement) * p_deltaTime * *speed);

			startingRotation = transform->GetLocalRotation();
			desiredRotation = Math::Quaternion::QuatFromEuler(Math::Vector3(0.f, atan2f(movement.x, movement.z) * Math::RAD2DEG, 0.f));
			if (curTime > totalSlerpTime)
			{
				transform->SetRotation(desiredRotation);
			}
			if (playerAttack && playerAttack->GetIsAttacking())
			{
				transform->SetRotation(Math::Quaternion::Slerp(startingRotation, desiredRotation, curTime * .1f));
			}
			else
			{
				transform->SetRotation(Math::Quaternion::Slerp(startingRotation, desiredRotation, curTime));
			}

			transform->Update();

			col->SetModified();
			col->Update(p_deltaTime, p_inputs);
			col->Update(p_deltaTime, p_inputs);

			curTime += p_deltaTime;
		}
		if (gameObject->transform.parentTransform && Math::Quaternion::Angle(desiredRotation, gameObject->transform.parentTransform->GetLocalRotation()) < 1.f)
		{
			curTime = 0.f;
			return;
		}
	}

	bool MoveCamera::PtrCheck()
	{
		if (col && playerAttack && lifeScript)
		{
			return true;
		}

		DataStructure::GameObject* playerObj = gameObject->Find("Player");

		if (!col)
		{
			col = playerObj->GetComponent<MonoBehavior::Physics::Collider>();
		}

		if (!playerAttack)
		{
			playerAttack = playerObj->GetComponent<PlayerAttack>();
		}

		if (!lifeScript)
		{
			lifeScript = playerObj->GetComponent<LifeScript>();
			if (lifeScript)
			{
				lifeScript->SetMaxLife(10);
			}
		}

		return col && playerAttack && lifeScript;
	}
}
