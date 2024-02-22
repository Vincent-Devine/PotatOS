#pragma once
#include <DLLInclude.hpp>

#include <vector>

#include <Common.hpp>
#include <Core/Scene.hpp>

namespace Core
{
	class POTATOS_ENGINE_API Engine
	{
	// Attributes
	private:
		std::vector<Scene*> scenes;
		Scene* currentScene;
		unsigned int witdh, height;
		GAMESTATE gameState;
		float timer;

	// Methods
	public:
		void Init(const int p_width, const int p_height);
		void Update(const float p_deltaTime, const Inputs& p_inputs, bool p_hasEditor = true);
		void Destroy();

		void ChangeScene(const char* p_name);
		void ChangeGameState();
		void ChangePreview(const char* p_previewFile, const char* p_filename);

		Scene* GetCurrentScene() { return currentScene; };
		std::vector<Scene*>& GetScenes() { return scenes; };
		const GAMESTATE& GetGameState() const { return gameState; };
		void CreateScene(const char* p_name);

	private:
		std::string GetFileNameOfPreviewScene(const char* p_nameModelToPreview);
	};
}
