#pragma once

#include <Input/InputManager.hpp>
#include <DataStructure/GameObject.hpp>
#include <Refureku/Refureku.h>
#include <Refureku/Generated/IComponent.rfkh.h>

namespace DataStructure
{
	class LightManager;
}

namespace MonoBehavior RFKNamespace()
{
	namespace Renderer 
	{
		class Camera;
	}

	enum COMPONENT_TYPE
	{
		NONE,
		CAMERA,
		POINT_LIGHT,
		SPOT_LIGHT,
		DIRECTIONAL_LIGHT,
		CAPSULE_COLLIDER,
		SPHERE_COLLIDER,
		BOX_COLLIDER,
		PLANE_COLLIDER,
		AUDIOSOURCE,
		ANIMATOR,
		CANVA,
		MODEL,
		SCRIPT,
	};

	class RFKClass() IComponent
	{
		// Attributes
	public:
		DataStructure::GameObject* gameObject;
		COMPONENT_TYPE componentType = NONE;
		
	protected:
		GAMESTATE* gameState = nullptr;

	private:
		bool isActive = true;

	// Methods
	public:
		virtual void Start(GAMESTATE * p_gameState) { gameState = p_gameState; };
		virtual void Update(const float p_deltaTime, const Inputs& p_inputs) {};
		virtual void Draw(const MonoBehavior::Renderer::Camera* p_camera, const DataStructure::LightManager& p_lightManager, const MonoBehavior::Renderer::Light* p_light = nullptr) const {};
		virtual void Destroy() {};
		void SetIsActive(const bool p_isActive) { isActive = p_isActive; };
		bool IsActive() { return isActive; };
		void ToggleActive() { isActive = !isActive; };
		
		MonoBehavior_IComponent_GENERATED
	};
}
File_IComponent_GENERATED