#include "pch.h"

#include <Core/Engine.hpp>
#include <Resource/Texture.hpp>
#include <Resource/Shader.hpp>
#include <Resource/Mesh.hpp>
#include <MonoBehavior/Renderer/Model.hpp>
#include <Core/ThreadPool.hpp>
#include <Wrapper/JsonLayer.hpp>
#include <Core/ResourceManager.hpp>
#include <MonoBehavior/Scripts/LifeDisplay.hpp>

namespace Core
{
	void Engine::Init(const int p_width, const int p_height)
	{
		witdh = p_width;
		height = p_height;

		gameState = GAMESTATE::EDIT;

		ThreadPool::Get()->Init();
		Wrapper::Physic::Get()->Init();

		scenes.push_back(new Scene("Level 1", gameState, SceneType::Scene));
		currentScene = scenes[0];
		currentScene->PreInit();
		Wrapper::LoadSave(currentScene);
		currentScene->Init(p_width, p_height);
		timer = 0.f;
	}

	void Engine::Update(const float p_deltaTime, const Inputs& p_inputs, bool p_hasEditor)
	{
		if (gameState == GAMESTATE::PLAY && p_inputs.restart && MonoBehavior::Script::LifeDisplay::gameOver)
		{
			MonoBehavior::Script::LifeDisplay::gameOver = false;
			ChangeGameState();
			ChangeGameState();
		}

		ThreadPool* threadPool = ThreadPool::Get();
		threadPool->Update();

		currentScene->Update(p_deltaTime, p_inputs);


		if (!p_hasEditor && gameState == GAMESTATE::EDIT && timer > 5.f && threadPool->FinishLoad())
		{
			gameState = GAMESTATE::PLAY;
		}
		timer += p_deltaTime;

	}

	void Engine::Destroy()
	{
		if (gameState == GAMESTATE::EDIT)
		{
			Wrapper::Save(currentScene);
		}
		currentScene->Destroy();
		for (Scene* scene : scenes)
		{
			delete scene;
		}
		Wrapper::Physic::Get()->Cleanup();
		ThreadPool::Get()->Delete();
	}

	void Engine::ChangeScene(const char* p_name)
	{
		if (p_name == currentScene->GetName())
		{
			return;
		}
		if (gameState == GAMESTATE::EDIT)
		{
			Wrapper::Save(currentScene);
		}
		currentScene->Destroy();
		Log::Print("------------------", LOG_LEVEL_TYPE::Notification);
		Log::Print("   Change Scene   ", LOG_LEVEL_TYPE::Notification);
		Log::Print("------------------", LOG_LEVEL_TYPE::Notification);

		Scene* scene = new Scene(p_name, gameState, SceneType::Scene);
		scenes.push_back(scene);
		currentScene = scene;
		currentScene->PreInit();
		Wrapper::LoadSave(currentScene);
		currentScene->Init(witdh, height);
	}

	void Engine::ChangeGameState()
	{
		if (gameState == GAMESTATE::EDIT)
		{
			gameState = GAMESTATE::PLAY;
		}
		else
		{
			gameState = GAMESTATE::EDIT;
		}
		currentScene->ChangeGameState();
	}

	void Engine::ChangePreview(const char* p_previewFile, const char* p_filename)
	{
		if (gameState == GAMESTATE::EDIT)
		{
			Wrapper::Save(currentScene);
		}
		currentScene->Destroy();
		Log::Print("------------------", LOG_LEVEL_TYPE::Notification);
		Log::Print("  Preview Scene   ", LOG_LEVEL_TYPE::Notification);
		Log::Print("------------------", LOG_LEVEL_TYPE::Notification);
		std::string filename = GetFileNameOfPreviewScene(p_previewFile);
		Scene* scene = new Scene(p_filename, gameState, SceneType::Preview);
		currentScene = scene;
		DataStructure::GameObject* GOPreview = currentScene->AddGameObject(p_filename, DataStructure::Transform(Math::Vector3(0.f, -0.5f, -5.f)));
		GOPreview->AddComponent
		(
			new MonoBehavior::Renderer::Model
			(
				Core::ResourceManager::Get()->UseMesh(filename),
				Core::ResourceManager::Get()->UseShader("Resources/Shaders/BlinnPhong.vert", "Resources/Shaders/BlinnPhong.frag"),
				nullptr
			)
		);
		DataStructure::GameObject* GOLight = currentScene->AddGameObject("light", DataStructure::Transform());
		currentScene->AddLight
		(
			GOLight,
			new MonoBehavior::Renderer::DirectionalLight(
				{
					Math::Vector4(0.1f, 0.1f, 0.1f),
					Math::Vector4(0.5f, 0.5f, 0.5f),
					Math::Vector4(1.0f, 1.0f, 1.0f),
				},
				Math::Vector3(0.f, 0.f, -1.f)
			)
		);
		currentScene->Init(witdh, height);
	}

	std::string Engine::GetFileNameOfPreviewScene(const char* p_nameModelToPreview)
	{
		std::string name(p_nameModelToPreview);
		for (unsigned int i = 0; i < name.size(); i++)
		{
			if(name[i] == '\\')
				name.replace(i, 1, "/");
		}
		name = "Resources/" + name; 
		return name;
	}

	void Engine::CreateScene(const char* p_name)
	{
		scenes.push_back(new Scene(p_name, gameState, SceneType::Scene));
		if (gameState == GAMESTATE::EDIT)
		{
			Wrapper::Save(scenes.back());
		}
	}
}
