#pragma once

#include "DataStructure/GameObject.hpp"
#include "Core/Engine.hpp"

#include <ImGUI/Include/imgui.h>
#include "imgui_internal.h"
#include "ImGuizmo/ImGuizmo.h"

namespace UI
{
	class Guizmo
	{
		// Attributes
	private:
		Core::Engine* engine;
		ImGuizmo::OPERATION operation;

		// Methods
	public:
		void Init(Core::Engine* p_engine);
		void Draw(DataStructure::GameObject* p_gameObjectSelected);

	private:
		void Input();

		void SetUpImGuizmo();
	};
}