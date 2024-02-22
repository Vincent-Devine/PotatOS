#include "pch.h"

#include <Application.hpp>

#include <DebugSystem/Assertion.hpp>
#include <Core/AnimationManager.hpp>
#include <Core/ResourceManager.hpp>
#include <Wrapper/JsonLayer.hpp>
#include <MonoBehavior/Scripts/MenuScript.hpp>
#include <MonoBehavior/Scripts/LifeDisplay.hpp>

bool Application::hasEditor = false;

bool Application::Init()
{
	Log::OpenFile("Log.txt");

	const int width = 1980;
	const int height = 1080;
	window = Wrapper::Window::Get();
	window->Create("PotatOS", width, height);
	rhi = Wrapper::RHI::Get();
	rhi->Init(width, height);
	
	engine.Init(width, height);

	soundLayer = Wrapper::SoundLayer::Get();
	inputManager = Input::InputManager::Get();

	Wrapper::LoadConfig(inputManager);

	Log::Print("Finish Init.", LOG_LEVEL_TYPE::Notification);
	return true;
}

void Application::Update(bool p_hasEditor)
{
	startTime = std::chrono::high_resolution_clock::now();
	hasEditor = p_hasEditor;

	window->Update();
	Inputs inputs = inputManager->Update(*window, engine.GetGameState());
	engine.Update(deltaTime, inputs, p_hasEditor);
	soundLayer->Update(engine.GetCurrentScene()->GetCamera()->gameObject->transform.GetPosition());
}

void Application::Render()
{
	window->Render();
	
	if (!MonoBehavior::Script::MenuScript::showMenu && !MonoBehavior::Script::LifeDisplay::gameOver)
	{
		currentTime = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	}
	else
	{
		deltaTime = 0.f;
	}
}

void Application::Destroy()
{
	Wrapper::SaveConfig(inputManager);
	
	engine.Destroy();
	rhi->Destroy();
	window->Destroy();

	Core::AnimationManager::Get()->Delete();

	Log::Print("Delete.", LOG_LEVEL_TYPE::Notification);
}

void Application::DisplayGame()
{
	rhi->DisplayTexture(rhi->GetTextureToRender());
}
