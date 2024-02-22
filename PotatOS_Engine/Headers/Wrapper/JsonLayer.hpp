#pragma once

#include <DLLInclude.hpp>
#include <Core/Scene.hpp>
#include <Input/InputManager.hpp>

namespace Wrapper
{
	void POTATOS_ENGINE_API Save(Core::Scene* p_scene);
	void POTATOS_ENGINE_API LoadSave(Core::Scene* p_scene);
	void POTATOS_ENGINE_API SaveConfig(Input::InputManager* p_inputManager);
	void POTATOS_ENGINE_API LoadConfig(Input::InputManager* p_inputManager);
}
