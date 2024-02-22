#pragma once

#include <DLLInclude.hpp>
#include <MonoBehavior/Renderer/Camera.hpp>
#include <DataStructure/GameObject.hpp>
#include <DataStructure/LightManager.hpp>
#include <DataStructure/GraphScene.hpp>
#include <Wrapper/Physic.hpp>
#include <MonoBehavior/AudioSource.hpp>

namespace Core
{
	enum class SceneType
	{
		Scene,
		Loading,
		Preview
	};

	class POTATOS_ENGINE_API Scene
	{
	// Attributes
	private:
		MonoBehavior::Renderer::Camera* camera;
		MonoBehavior::Renderer::Camera* editCamera;
		std::vector<DataStructure::GameObject*> gameObjects;
		DataStructure::LightManager lightManager;
		DataStructure::GraphScene graphScene;
		
		std::string name;

		GAMESTATE& gameState;
		SceneType sceneType;

	// Methods
	public:
		Scene(const std::string& p_name, GAMESTATE& p_gameState, const SceneType p_sceneType);

		void PreInit();

		void Init(const int p_width, const int p_height);
		void Update(const float p_deltaTime, const Inputs& p_inputs);
		void Draw() const;
		void DrawFromLightPosition(MonoBehavior::Renderer::Light* p_light = nullptr) const;
		void Destroy();

		std::vector<DataStructure::GameObject*>& GetGameObjects() { return gameObjects; };
		DataStructure::LightManager& GetLightManager() { return lightManager; };
		DataStructure::GraphScene& GetGraphScene() { return graphScene; };
		const std::string& GetName() const { return name; };
		const Math::Vector3& GetCameraPosition();
		MonoBehavior::Renderer::Camera* GetCameraEditor() { return editCamera; };
		SceneType GetSceneType() { return sceneType; };
		MonoBehavior::Renderer::Camera* GetCamera() { if (gameState == GAMESTATE::EDIT) return editCamera; else return camera; };
		GAMESTATE& GetGameState() { return gameState; };

		void AddCamera(DataStructure::GameObject* p_gameObject, bool p_isCameraEditor = false);
		DataStructure::GameObject* AddGameObject(const std::string& p_name, const DataStructure::Transform& p_transform, DataStructure::GameObject* p_parent = nullptr);
		void AddLight(DataStructure::GameObject* p_gameObject, MonoBehavior::Renderer::Light* p_light);

		void ChangeGameState();
	};
}
