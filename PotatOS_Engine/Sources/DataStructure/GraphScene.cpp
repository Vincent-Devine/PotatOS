#include "pch.h"

#include <DataStructure/GraphScene.hpp>
#include <DebugSystem/Assertion.hpp>

namespace DataStructure
{
	void GraphScene::Draw(const MonoBehavior::Renderer::Camera* p_camera, const LightManager& p_lightManager, const MonoBehavior::Renderer::Light* p_light) const
	{
		nodes[0]->gameObject->Draw(p_camera, p_lightManager, p_light);
		
		for (GraphNode* childNode : nodes[0]->children)
		{
			DrawChild(p_camera, p_lightManager, childNode, p_light);
		}
	}

	void GraphScene::DrawChild(const MonoBehavior::Renderer::Camera* p_camera, const LightManager& p_lightManager, const GraphNode* p_node, const MonoBehavior::Renderer::Light* p_light) const
	{
		p_node->gameObject->Draw(p_camera, p_lightManager, p_light);

		for (GraphNode* childNode : p_node->children)
		{
			DrawChild(p_camera, p_lightManager, childNode, p_light);
		}
	}

	void GraphScene::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		UpdateNode(nodes[0], p_deltaTime, p_inputs);
	}

	GameObject* GraphScene::FindByName(const std::string& p_name)
	{
		for (GraphNode* node : nodes)
		{
			if (node->gameObject->GetName() == p_name)
			{
				return node->gameObject;
			}
		}
		return nullptr;
	}

	void GraphScene::UpdateNode(GraphNode* p_node, const float p_deltaTime, const Inputs& p_inputs)
	{
		p_node->gameObject->Update(p_deltaTime, p_inputs);
		if (p_node->gameObject->transform.IsDirty())
		{
			SetChildrenDirty(p_node);
			p_node->gameObject->transform.Update();
		}
		for (GraphNode* childNode : p_node->children)
		{
			UpdateNode(childNode, p_deltaTime, p_inputs);
		}
	}

	void GraphScene::AddToGraphScene(GameObject* p_gameObject, GameObject* p_parent)
	{
		GraphNode* parentNode = nullptr;

		if (p_parent)
		{
			parentNode = GetNode(p_parent);
			p_gameObject->transform.parentTransform = &p_parent->transform;
		}
		else if(nodes.size() > 0 && p_gameObject != nodes[0]->gameObject)
		{
			parentNode = nodes[0];
			p_gameObject->transform.parentTransform = &nodes[0]->gameObject->transform;
		}
		
		GraphNode* curNode = new GraphNode{ p_gameObject, parentNode };
		p_gameObject->transform.gameObject = p_gameObject;
		p_gameObject->SetGraph(this);
		nodes.push_back(curNode);
		
		if (parentNode)
		{
			parentNode->children.push_back(curNode);
			parentNode->gameObject->transform.children.push_back(&curNode->gameObject->transform);
		}
	}

	void GraphScene::SetChildrenDirty(const GraphNode* p_node)
	{
		for (GraphNode* childNode : p_node->children)
		{
			childNode->gameObject->transform.SetDirty();
			SetChildrenDirty(childNode);
		}
	}

	GraphNode* GraphScene::GetNode(const GameObject* p_gameObject)
	{
		for (GraphNode* node : nodes)
		{
			if (p_gameObject == node->gameObject)
			{
				return node;
			}
		}
		Log::Print("GameObject not found !", LOG_LEVEL_TYPE::Critical);
		return nullptr;
	}
}
