#pragma once

#include <DLLInclude.hpp>
#include <vector>

#include <DataStructure/Transform.hpp>
#include <Common.hpp>


namespace MonoBehavior
{
	class IComponent;
	class Animator;
	namespace Renderer
	{
		class Camera;
		class Light;
	}
	namespace Physics
	{
		class Collider;
	}
}

namespace DataStructure
{
	class GraphScene;
}

namespace DataStructure
{
	class LightManager;

	class POTATOS_ENGINE_API GameObject
	{
	// Attributes
	public:
		Transform transform;
		std::vector<MonoBehavior::IComponent*> components;
	private:
		std::string name;
		Transform initTransform;
		bool isSelected = false;
		DataStructure::GraphScene* graphScene;

	// Methods
	public:
		GameObject(const std::string& p_name, const Transform p_transform = Transform());

		void Start(GAMESTATE* p_gameState);
		void Update(const float p_deltaTime, const Inputs& p_inputs);
		void Draw(const MonoBehavior::Renderer::Camera* p_camera, const LightManager& p_lightManagerm, const MonoBehavior::Renderer::Light* p_light = nullptr) const;
		void Destroy();

		void AddComponent(MonoBehavior::IComponent* p_newComponent, const bool p_isCamera = false);

		void ChangeGameState(GAMESTATE p_gameState);

		MonoBehavior::Physics::Collider* GetCollider();
		MonoBehavior::Animator* GetAnimator();

		MonoBehavior::IComponent* CreateComponent(int p_compType);

		GameObject* Find(const std::string& p_name);

		const std::string& GetName() const { return name; };
		void SetName(const std::string& p_name) { name = p_name; };
		void SetSelected(bool p_selected) { isSelected = p_selected; };
		bool IsSelected() { return isSelected; };
		void SetGraph(DataStructure::GraphScene* p_graph) { graphScene = p_graph; };

		template <class T>
		T* GetComponent()
		{
			T* res = nullptr;
			for (MonoBehavior::IComponent* component : components)
			{
				res = dynamic_cast<T*>(component);
				if (res)
				{
					break;
				}
			}
			return res;
		};
	};
}
