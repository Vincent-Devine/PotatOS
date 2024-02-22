#pragma once

#include <DLLInclude.hpp>
#include <Wrapper/RHI.hpp>
#include <Wrapper/Window.hpp>
#include <Core/Engine.hpp>
#include <Input/InputManager.hpp>
#include <Wrapper/SoundLayer.hpp>

class POTATOS_ENGINE_API Application
{
// Attributes
private:
	Wrapper::RHI* rhi;
	Wrapper::Window* window;
	Wrapper::SoundLayer* soundLayer;

	Input::InputManager* inputManager;

	Core::Engine engine;

	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point currentTime;
	float deltaTime = 0.f;

public:
	static bool hasEditor;

// Methods
public:
	bool Init();
	void Update(bool p_hasEditor = true);
	void Render();
	void Destroy();

	void DisplayGame();

	const bool WindowShouldClose() const { return window->WindowShouldClose(); };

	Core::Engine& GetEngine() { return engine; };
	Wrapper::RHI& GetRHI() { return *rhi; };
	Wrapper::Window& GetWindow() { return *window; };
	Input::InputManager& GetInputManager() { return *inputManager; };
};
