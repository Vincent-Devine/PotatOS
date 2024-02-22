#include "GraphScene.hpp"

namespace UI
{
	void SceneGraph::Draw(Core::Scene* p_scene)
	{

		ImGui::Begin("SceneGraph");

		AddGameObject(p_scene);

		std::vector<DataStructure::GraphNode*> nodes = p_scene->GetGraphScene().GetNodes();
		InitGameObjectsWindow();

		if (ImGui::BeginListBox("GameObjects", ImVec2(-1,-1)))
		{
			UIKeysPressed(currentSelectedIndex, nodes);

			for (int n = 0; n < nodes.size(); ++n)
			{

				isSelected = (currentSelectedIndex == n);

				if (nodes[n]->parent != nullptr)
				{
					continue;
				}

				if (ImGui::Selectable(nodes[n]->gameObject->GetName().c_str(), isSelected))
				{
					currentSelectedIndex = -1;
					if (gameObjectSelected)
					{
						gameObjectSelected->SetSelected(false);
					}
					gameObjectSelected = nodes[n]->gameObject;
					gameObjectSelected->SetSelected(true);
					colliderSelected = nullptr;
					for (MonoBehavior::IComponent* component : gameObjectSelected->components)
					{
						colliderSelected = dynamic_cast<MonoBehavior::Physics::Collider*>(component);
						if (colliderSelected)
						{
							break;
						}
					}
				}
				indentParent = 0;
				DrawChildSceneGraph(p_scene->GetGraphScene(), nodes[n]);
			}
			ImGui::EndListBox();
		}
		ImGui::PopStyleVar();
		ImGui::End();
	}

	void SceneGraph::InitGameObjectsWindow()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2());
	}

	void SceneGraph::UIKeysPressed(int& p_currentSelectedIndex, std::vector<DataStructure::GraphNode*> p_nodes)
	{
		if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_DownArrow)))
		{
			if (p_currentSelectedIndex < p_nodes.size() - 1)
			{
				++p_currentSelectedIndex;
			}
		}
		if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_UpArrow)))
		{
			if (p_currentSelectedIndex > 0)
			{
				--p_currentSelectedIndex;
			}
		}
	}

	void SceneGraph::DrawChildSceneGraph(const DataStructure::GraphScene& p_scenegraph, const DataStructure::GraphNode* p_node)
	{
		indentParent++;
		for (int i = 0; i < p_node->children.size(); i++)
		{
			if (p_node->children[i]->gameObject->GetName() == "Camera Editor")
			{
				continue;
			}

			indentChildren++;
			indentChildren += indentParent;
			for (size_t i = 0; i < indentChildren; i++)
			{
				ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
			}

			if (ImGui::Selectable(p_node->children[i]->gameObject->GetName().c_str(), isSelected))
			{
				currentSelectedIndex = -1;
				if (gameObjectSelected)
				{
						gameObjectSelected->SetSelected(false);
				}
				gameObjectSelected = p_node->children[i]->gameObject;
				gameObjectSelected->SetSelected(true);
				colliderSelected = nullptr;
				for (MonoBehavior::IComponent* component : gameObjectSelected->components)
				{
					colliderSelected = dynamic_cast<MonoBehavior::Physics::Collider*>(component);
					if (colliderSelected)
					{
						break;
					}
				}
			}

			for (size_t i = 0; i < indentChildren; i++)
			{
				ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());
			}
			indentChildren = 0;
			DrawChildSceneGraph(p_scenegraph, p_node->children[i]);
			indentParent--;
		}
	}

	void SceneGraph::IndentSetBack()
	{

		for (size_t i = 0; i < indentChildren; i++)
		{
			ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());
		}
		indentChildren = 0;
	}

	void SceneGraph::DragAndDrop()
	{
		for (size_t i = 0; i < nodes.size(); i++)
		{
			ImGui::SetDragDropPayload("GameObjectsList", &i, sizeof(DataStructure::GraphNode));
		}

		if (ImGui::BeginDragDropSource())
		{
			ImGui::Text("This is a drag and drop source");

			if (ImGui::BeginDragDropTarget())
			{
				const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GameObjectsList");
				if (payload)
				{
					ImGui::Text("Dropped");
				}
				ImGui::EndDragDropTarget();
			}
			ImGui::EndDragDropSource();
		}
	}

	void SceneGraph::AddGameObject(Core::Scene* p_scene)
	{
		static char name[64] = "Name of game object";
		if (ImGui::Button("Add Game Object"))
		{
			ImGui::OpenPopup("Game Object");
		}
		if (ImGui::BeginPopup("Game Object"))
		{
			ImGui::Text("Name of your Game Object");
			ImGui::InputText("Name", name, IM_ARRAYSIZE(name));

			static int itemIndexObjects = 0;
			if (ImGui::Button("Set Parent "))
			{
				ImGui::OpenPopup("Parents availables");
			}

			if (ImGui::BeginPopup("Parents availables"))
			{
				if (ImGui::BeginListBox("Parents Availables"))
				{
					for (int n = 0; n < p_scene->GetGameObjects().size(); n++)
					{
						const bool is_selected = (itemIndexObjects == n);
						if (ImGui::Selectable(p_scene->GetGameObjects()[n]->GetName().c_str(), is_selected))
						{
							itemIndexObjects = n;
						}

						// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
						if (is_selected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndListBox();
				}

				ImGui::EndPopup();
			}

			ImGui::SameLine();
			HelpMarker
			(
				"Enter the name of the created game object.\n" 
				"-- WARNING ! --\n"
				"The name cannot be empty"
			);
			if (ImGui::Button("Ok"))
			{
				if (std::strlen(name) != 0)
				{
					p_scene->AddGameObject(std::string(name), DataStructure::Transform(), p_scene->GetGameObjects()[itemIndexObjects]);
					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

	void SceneGraph::HelpMarker(const char* p_desc)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(p_desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

}
