#include "pch.h"

#include <DebugSystem/Assertion.hpp>
#include <Core/Scene.hpp>
#include <Core/ResourceManager.hpp>
#include <Core/AnimationManager.hpp>
#include <MonoBehavior/MoveCameraEditor.hpp>
#include <MonoBehavior/RandomRotation.hpp>

namespace Core
{
	Scene::Scene(const std::string& p_name, GAMESTATE& p_gameState, const SceneType p_sceneType)
		: name(p_name)
		, editCamera(nullptr)
		, gameState(p_gameState)
		, sceneType(p_sceneType)
	{
	}

	void Scene::PreInit()
	{
		AddGameObject("Root", DataStructure::Transform());
	}
	void Scene::Init(const int p_width, const int p_height)
	{

		DataStructure::GameObject* cameraEditor = AddGameObject("Camera Editor", DataStructure::Transform());
		AddCamera(cameraEditor, true);
		cameraEditor->AddComponent(new MonoBehavior::MoveCameraEditor);

		if (editCamera)
		{
			editCamera->Init(p_width, p_height);
		}

		if (camera)
		{
			camera->Init(p_width, p_height);
		}

		for (DataStructure::GameObject* gameObject : gameObjects)
		{
			gameObject->Start(&gameState);
		}
	}

	void Scene::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (gameState == GAMESTATE::PLAY)
		{
			Wrapper::Physic::Get()->Update();
		}

		graphScene.Update(p_deltaTime, p_inputs);
	}

	void Scene::Draw() const
	{
		if (gameState == GAMESTATE::PLAY)
		{
			graphScene.Draw(camera, lightManager);
		}
		else
		{
			graphScene.Draw(editCamera, lightManager);
		}
	}

	void Scene::DrawFromLightPosition(MonoBehavior::Renderer::Light* p_light) const
	{
		graphScene.Draw(camera, lightManager, p_light);
	}

	void Scene::Destroy()
	{
		for (DataStructure::GameObject* gameObject : gameObjects)
		{
			gameObject->Destroy();
			delete gameObject;
		}
	}

	void Scene::AddCamera(DataStructure::GameObject* p_gameObject, bool p_isCameraEditor)
	{
		if (p_isCameraEditor)
		{
			editCamera = new MonoBehavior::Renderer::Camera;
			p_gameObject->AddComponent(editCamera, true);
		}
		else
		{
			camera = new MonoBehavior::Renderer::Camera;
			p_gameObject->AddComponent(camera, true);
		}
	}

	DataStructure::GameObject* Scene::AddGameObject(const std::string& p_name, const DataStructure::Transform& p_transform, DataStructure::GameObject* p_parent)
	{
		DataStructure::GameObject* gameObject = new DataStructure::GameObject(p_name, p_transform);
		gameObjects.push_back(gameObject);
		graphScene.AddToGraphScene(gameObject, p_parent);
		Log::Print("Add GameObject " + gameObject->GetName() + " in scene.", LOG_LEVEL_TYPE::Notification);
		return gameObject;
	}

	void Scene::AddLight(DataStructure::GameObject* p_gameObject, MonoBehavior::Renderer::Light* p_light)
	{
		p_gameObject->AddComponent(p_light);

		if (dynamic_cast<MonoBehavior::Renderer::DirectionalLight*>(p_light))
		{
			lightManager.AddDirectionLight(dynamic_cast<MonoBehavior::Renderer::DirectionalLight*>(p_light));
		}
		else if (dynamic_cast<MonoBehavior::Renderer::SpotLight*>(p_light))
		{
			lightManager.AddSpotLight(dynamic_cast<MonoBehavior::Renderer::SpotLight*>(p_light));
		}
		else if (dynamic_cast<MonoBehavior::Renderer::PointLight*>(p_light))
		{
			lightManager.AddPointLight(dynamic_cast<MonoBehavior::Renderer::PointLight*>(p_light));
		}
	}


	void Scene::ChangeGameState()
	{
		if (!camera)
		{
			gameState = GAMESTATE::EDIT;
			Log::Print("No camera in the scene!", LOG_LEVEL_TYPE::Warning);
		}

		for (DataStructure::GameObject* gameObject : gameObjects)
		{
			gameObject->ChangeGameState(gameState);
		}
		Wrapper::Physic::Get()->Update();
	}

	const Math::Vector3& Scene::GetCameraPosition()
	{
		if (gameState == GAMESTATE::EDIT)
		{
			return editCamera->gameObject->transform.GetPosition();
		}
		else
		{
			return camera->gameObject->transform.GetPosition();
		}
	}
}
