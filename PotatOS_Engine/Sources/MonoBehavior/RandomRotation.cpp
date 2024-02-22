#include "pch.h"
#include <MonoBehavior/RandomRotation.hpp>

namespace MonoBehavior
{
	RandomRotation::RandomRotation():
		timer(0),
		timeNewRotation(215),
		rotation(Math::Vector3(0.f, 0.f, 1.f)),
		speed(5.f)
	{
	}

	void RandomRotation::Start(GAMESTATE* p_gameState)
	{
		componentType = SCRIPT;
		gameState = p_gameState;
		t = 0.f;
	}

	void RandomRotation::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (*gameState == GAMESTATE::EDIT)
		{
			return;
		}

		if (t > 0.95f)
		{
			t = 0.f;
		}

		if (t == 0.f)
		{
			startingRotation = gameObject->transform.GetLocalRotation();

			rotation = Math::Vector3(rand() % 360 * 1.f, rand() % 360 * 1.f, rand() % 360 * 1.f);
			if (rotation.x > 180.f)
			{
				rotation.x -= 360.f;
			}
			if (rotation.y > 180.f)
			{
				rotation.y -= 360.f;
			}
			if (rotation.z > 180.f)
			{
				rotation.z -= 360.f;
			}

			desiredRotation = Math::Quaternion::QuatFromEuler(rotation);
		}

		gameObject->transform.SetRotation(Math::Quaternion::Slerp(startingRotation, desiredRotation, t));

		t += p_deltaTime;
	}
}
