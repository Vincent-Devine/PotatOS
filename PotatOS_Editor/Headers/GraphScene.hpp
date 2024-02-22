#pragma once

#include <ImGUI/Include/imgui.h>
#include <Core/Scene.hpp>
#include <MonoBehavior/Physics/Collider.hpp>

namespace UI
{
	class SceneGraph
	{
		// Attributes
	private:
		int currentSelectedIndex = -1;
		ImVec2 gameObjectsListSize;
		std::vector<DataStructure::GraphNode> nodes;
		DataStructure::GameObject* gameObjectSelected = nullptr;
		MonoBehavior::Physics::Collider* colliderSelected = nullptr;
		unsigned int indentParent = 0;
		bool isSelected;
		unsigned int indentChildren = 0;

		// Methods
	public:
		void Draw(Core::Scene* p_scene);

		DataStructure::GameObject* GetGameObjectSelected() { return gameObjectSelected; };
		MonoBehavior::Physics::Collider* GetColliderSelected() { return colliderSelected; };

	private:
		void InitGameObjectsWindow();
		void UIKeysPressed(int& p_currentSelectedIndex, std::vector<DataStructure::GraphNode*> p_nodes);
		void DrawChildSceneGraph(const DataStructure::GraphScene& p_scenegraph, const DataStructure::GraphNode* p_node);
		void IndentSetBack();
		void DragAndDrop();

		void AddGameObject(Core::Scene* p_scene);
		void HelpMarker(const char* p_desc);
	};
}
