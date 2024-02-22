#pragma once

#include <DLLInclude.hpp>
#include <vector>

#include <DataStructure/GameObject.hpp>
#include <DataStructure/LightManager.hpp>
#include <MonoBehavior/Renderer/Camera.hpp>

namespace DataStructure
{
	struct GraphNode
	{
		GraphNode(const GraphNode& node) : gameObject(node.gameObject), parent(node.parent), children(node.children) {};
		GraphNode(DataStructure::GameObject* p_gameObject, GraphNode* p_parent = nullptr) : gameObject(p_gameObject), parent(p_parent) {};
		~GraphNode() { std::cout << gameObject->GetName() << " is being deleted from scene graph" << std::endl; };
		GameObject* gameObject = nullptr;
		GraphNode* parent = nullptr;
		std::vector<GraphNode*> children;
	};

	class GraphScene
	{
	// Attributes
	private:
		std::vector<GraphNode*> nodes;

	// Methods
	public:
		void Draw(const MonoBehavior::Renderer::Camera* p_camera, const LightManager& p_lightManager, const MonoBehavior::Renderer::Light* p_light = nullptr) const;
		void Update(const float p_deltaTime, const Inputs& p_inputs);

		void AddToGraphScene(GameObject* p_gameObject, GameObject* p_parent = nullptr);

		std::vector<GraphNode*> GetNodes() const { return nodes; };

		GameObject* FindByName(const std::string& p_name);

	private:
		void UpdateNode(GraphNode* p_node, const float p_deltaTime, const Inputs& p_inputs);
		void SetChildrenDirty(const GraphNode* p_node);
		void DrawChild(const MonoBehavior::Renderer::Camera* p_camera, const LightManager& p_lightManager, const GraphNode* p_node, const MonoBehavior::Renderer::Light* p_light = nullptr) const;

		GraphNode* GetNode(const GameObject* p_gameObject);
	};
}
