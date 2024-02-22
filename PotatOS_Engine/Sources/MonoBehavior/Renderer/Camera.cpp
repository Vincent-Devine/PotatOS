#include "pch.h"

#include <MonoBehavior/Renderer/Camera.hpp>
#include <MonoBehavior/Scripts/MenuScript.hpp>
#include <Core/ThreadPool.hpp>
#include <Application.hpp>

namespace MonoBehavior::Renderer
{
	void Camera::Init(const int p_width, const int p_height)
	{
		componentType = CAMERA;
		zFar = 1000.f;
		zNear = 0.1f;
		FOV = Math::DEG2RAD * 90.f;
		speed = 2.0f;
		aspect = ((float)p_width / (float)p_height);
		CalcProjection();
	}

	void Camera::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		CalcView();
	}

	void Camera::CalcView()
	{
		if (!Application::hasEditor && !Core::ThreadPool::Get()->FinishLoad())
		{
			view = Math::Mat4::LookAt
			(
				Math::Vector3(500.f, 500.f, 500.f),		// Camera position
				Math::Vector3(-505.f, 500.f, 500.f),	// Target
				Math::Vector3(0.f, 1.f, 0.f)			// Up
			);

			gameObject->transform.SetPosition(Math::Vector3(-5.f, 8.f, 9.f) + gameObject->transform.parentTransform->GetPosition());
		}
		else if(*gameState == GAMESTATE::EDIT)
		{
			view =
				Math::Mat4::CreateXRotationMatrix(-rotation.x) *
				Math::Mat4::CreateYRotationMatrix(-rotation.y) *
				Math::Mat4::CreateTranslationMatrix(-gameObject->transform.GetPosition());
		}
		else
		{
			if (MonoBehavior::Script::MenuScript::showMenu)
			{
				view = Math::Mat4::LookAt
				(
					Math::Vector3(-1500.f, 500.f, 500.f) + gameObject->transform.parentTransform->GetPosition(),	// Camera position
					Math::Vector3(0.f, 1000.f, 0.f),															// Target
					Math::Vector3(0.f, 1.f, 0.f)																// Up
				);

				gameObject->transform.SetPosition(Math::Vector3(-5.f, 8.f, 9.f) + gameObject->transform.parentTransform->GetPosition());
			}
			else if(gameObject->transform.parentTransform)
			{
				
				view = Math::Mat4::LookAt
				(
					Math::Vector3(-5.f, 8.f, 9.f) + gameObject->transform.parentTransform->GetPosition(),		// Camera position
					gameObject->transform.parentTransform->GetPosition(),										// Target
					Math::Vector3(0.f, 1.f, 0.f)																// Up
				);

				gameObject->transform.SetPosition(Math::Vector3(-5.f, 8.f, 9.f) + gameObject->transform.parentTransform->GetPosition());
			}
		}
	}

	void Camera::CalcProjection()
	{
		projection = Math::Mat4::GetPerspectiveProjection(aspect, FOV, zNear, zFar);
	}
}
