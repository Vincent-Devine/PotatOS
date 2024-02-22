#include "pch.h"

#include <DataStructure/GameObject.hpp>
#include <DataStructure/LightManager.hpp>
#include <MonoBehavior/IComponent.hpp>
#include <MonoBehavior/Renderer/Camera.hpp>
#include <DebugSystem/Log.hpp>
#include <MonoBehavior/Physics/Collider.hpp>
#include <MonoBehavior/Animator.hpp>
#include <MonoBehavior/Canva.hpp>
#include <MonoBehavior/Physics/CapsuleCollider.hpp>
#include <MonoBehavior/Physics/BoxCollider.hpp>
#include <MonoBehavior/Physics/PlaneCollider.hpp>
#include <MonoBehavior/Physics/SphereCollider.hpp>
#include <MonoBehavior/Renderer/Model.hpp>
#include <MonoBehavior//AudioSource.hpp>
#include <DataStructure/GraphScene.hpp>
#include <MonoBehavior/LifeScript.hpp>
#include <MonoBehavior/BobScript.hpp>

namespace DataStructure
{
	GameObject::GameObject(const std::string& p_name, const Transform p_transform)
		: name(p_name)
		, transform(p_transform)
		, initTransform(p_transform)
	{
	}

	void GameObject::Start(GAMESTATE* p_gameState)
	{
		for (MonoBehavior::IComponent* component : components)
		{
			if (component->IsActive())
			{
				component->Start(p_gameState);
			}
		}
	}

	void GameObject::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		for (MonoBehavior::IComponent* component : components)
		{
			if (component->IsActive())
			{
				component->Update(p_deltaTime, p_inputs);
			}
		}
	}

	void GameObject::Draw(const MonoBehavior::Renderer::Camera* p_camera, const LightManager& p_lightManager, const MonoBehavior::Renderer::Light* p_light) const
	{
		for (MonoBehavior::IComponent* component : components)
		{
			if (component->IsActive())
			{
				component->Draw(p_camera, p_lightManager, p_light);
			}
		}
	}

	void GameObject::Destroy()
	{
		for (MonoBehavior::IComponent* component : components)
		{
			component->Destroy();
			delete component;
		}
	}

	void GameObject::AddComponent(MonoBehavior::IComponent* p_newComponent, const bool p_isCamera)
	{
		p_newComponent->gameObject = this;

		if (!p_isCamera && dynamic_cast<MonoBehavior::Renderer::Camera*>(p_newComponent))
		{
			Log::Print("Camera already exist", LOG_LEVEL_TYPE::Warning);
			
			delete p_newComponent;
			return;
		}

		components.push_back(p_newComponent);
	}

	void GameObject::ChangeGameState(GAMESTATE p_gameState)
	{
		if (p_gameState == GAMESTATE::PLAY) // Edit to Play
		{
			initTransform.SetPosition(transform.GetLocalPosition());
			initTransform.SetRotation(transform.GetLocalRotation());
			initTransform.SetScale(transform.GetLocalScale());
			initTransform.gameObject = transform.gameObject;
			initTransform.parentTransform = transform.parentTransform;
		}
		else // Play to Edit
		{
			initTransform.Update();
			transform.SetPosition(initTransform.GetLocalPosition());
			transform.SetRotation(initTransform.GetLocalRotation());
			transform.SetScale(initTransform.GetLocalScale());
			transform.gameObject = initTransform.gameObject;
			transform.parentTransform = initTransform.parentTransform;
			MonoBehavior::Physics::Collider* collider = GetCollider();
			if (collider)
			{
				collider->SetModified();
			}
			transform.Update();
			MonoBehavior::LifeScript* ls = GetComponent<MonoBehavior::LifeScript>();
			if (ls)
			{
				ls->ResetLife();
			}
			MonoBehavior::BobScript* bs = GetComponent<MonoBehavior::BobScript>();
			if (bs)
			{
				bs->Reset();
			}
		}
	}

	MonoBehavior::Physics::Collider* GameObject::GetCollider()
	{
		for (unsigned int i = 0; i < components.size(); i++)
		{
			MonoBehavior::Physics::Collider* collider = dynamic_cast<MonoBehavior::Physics::Collider*>(components[i]);
			if (collider)
			{
				return collider;
			}
		}
		return nullptr;
	}

	MonoBehavior::Animator* GameObject::GetAnimator()
	{
		for (unsigned int i = 0; i < components.size(); i++)
		{
			MonoBehavior::Animator* animator = dynamic_cast<MonoBehavior::Animator*>(components[i]);
			if (animator)
			{
				return animator;
			}
		}
		return nullptr;
	}

	MonoBehavior::IComponent* GameObject::CreateComponent(int p_compType)
	{
		switch (p_compType)
		{
		case 0:
		{
			MonoBehavior::Renderer::InitLight temp;
			MonoBehavior::Renderer::PointLight* tempPoint = new MonoBehavior::Renderer::PointLight(temp, 1.f, 1.f, 1.f);
			return tempPoint;
		}
		case 1:
		{
			MonoBehavior::Renderer::InitLight temp;
			MonoBehavior::Renderer::SpotLight* tempSpot = new MonoBehavior::Renderer::SpotLight(temp, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f);
			return tempSpot;
		}
		case 2:
		{
			MonoBehavior::Renderer::InitLight temp;
			MonoBehavior::Renderer::DirectionalLight* tempDir = new MonoBehavior::Renderer::DirectionalLight(temp, Math::Vector3(0.f, -1.f, 0.f));
			return tempDir;
		}
		case 3:
		{
			MonoBehavior::Physics::CapsuleCollider* tempCap = new MonoBehavior::Physics::CapsuleCollider();
			return tempCap;
		}
		case 4:
		{
			MonoBehavior::Physics::SphereCollider* tempSphere = new MonoBehavior::Physics::SphereCollider();
			return tempSphere;
		}
		case 5:
		{
			MonoBehavior::Physics::BoxCollider* tempBox = new MonoBehavior::Physics::BoxCollider();
			tempBox->gameObject = this;
			return tempBox;
		}
		case 6:
		{
			MonoBehavior::Physics::PlaneCollider* tempPlane = new MonoBehavior::Physics::PlaneCollider();
			return tempPlane;
		}
		case 7:
		{
			MonoBehavior::AudioSource* tempAudio = new MonoBehavior::AudioSource(Core::ResourceManager::Get()->UseSound("Resources/Sounds/wave.mp3"), 0, false, 0.5f, 100.f);
			return tempAudio;
		}
		case 8:
		{
			MonoBehavior::Animator* tempAnim = new MonoBehavior::Animator(nullptr, nullptr);
			return tempAnim;
		}
		case 9:
		{
			MonoBehavior::Canva* tempCanva = new MonoBehavior::Canva();
			return tempCanva;
		}
		case 10:
		{
			MonoBehavior::Renderer::Model* tempModel = new MonoBehavior::Renderer::Model(nullptr, nullptr, nullptr);
			return tempModel;
		}
		case 11:
		{
			//TODO Script
			break;
		}
		default:
			break;
		}
		return new MonoBehavior::IComponent;
	}

	GameObject* GameObject::Find(const std::string& p_name)
	{
		return graphScene->FindByName(p_name);
	}
}
