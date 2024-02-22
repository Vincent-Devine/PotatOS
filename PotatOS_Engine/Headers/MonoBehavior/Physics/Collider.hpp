#pragma once

#include <DLLInclude.hpp>

#include <MonoBehavior/IComponent.hpp>
#include <Wrapper/Physic.hpp>
#include <Math/Vector3.hpp>
#include <Resource/Shader.hpp>
#include <MonoBehavior/Renderer/Camera.hpp>
#include <DataStructure/LightManager.hpp>
#include <Resource/PrimitiveMesh.hpp>

#include <Refureku/Refureku.h>
#include <Refureku/Generated/Collider.rfkh.h>

namespace MonoBehavior::Physics RFKNamespace()
{
	class RFKClass() POTATOS_ENGINE_API Collider : public IComponent
	{
		// Attributes
	protected:
		bool modified = false;

		RFKField()
		bool lockPosX, lockPosY, lockPosZ, lockRotX, lockRotY, lockRotZ;

		RFKField()
		bool isStatic;
		Wrapper::Physic* physic = nullptr;

		RFKField()
		bool isTrigger;

		RFKField()
		bool queryable;
		uint32_t id;
		physx::PxRigidDynamic* rigidBody = nullptr;
		physx::PxRigidStatic* staticBody = nullptr;
		physx::PxRigidActor* baseActor = nullptr;
		physx::PxShape* shape = nullptr;
		Resource::PrimitiveMesh* pMesh = nullptr;
		DataStructure::Transform transform;

		RFKField()
		Math::Vector3 offset; 
		Math::Quaternion tilt;
		Math::Vector3 anti;

	private:
		Resource::Shader* shader = nullptr;

		// Methods
	public:
		Collider(const bool p_static = true, const bool p_trigger = false, const bool p_queryShape = false, const Math::Vector3& p_offset = Math::Vector3());

		void Start(GAMESTATE * p_gameState) override;
		void Update(const float p_deltaTime, const Inputs& p_inputs) override;
		void Draw(const MonoBehavior::Renderer::Camera* p_camera, const DataStructure::LightManager& p_lightManager, const MonoBehavior::Renderer::Light * p_light = nullptr) const override;
		void Destroy() override;
		void SetModified() { modified = true; };

		const bool IsStatic() const { return isStatic; };
		const bool IsTrigger() const { return isTrigger; };
		const bool Queryable() const { return queryable; };

		void ToggleStatic();
		void ToggleTrigger();
		void ToggleQueryable();

		const Math::Vector3& GetOffset() const { return offset; };
		physx::PxRigidActor* GetBaseActor() const { return baseActor; };
		physx::PxShape* GetShape() const { return shape; };
		void AxisLock();
		std::vector<OverlapHit> Overlap() { return physic->Overlap(*this); };
		void AddForce(const Math::Vector3& p_force, const bool p_isImpulse = false);
		void SetLock(const bool p_lockPosX, const bool p_lockPosY, const bool p_lockPosZ, const bool p_lockRotX, const bool p_lockRotY, const bool p_lockRotZ) { lockPosX = p_lockPosX; lockPosY = p_lockPosY; lockPosZ = p_lockPosZ; lockRotX = p_lockRotX; lockRotY = p_lockRotY; lockRotZ = p_lockRotZ; };
		bool GetLockPosX() const { return lockPosX; };
		bool GetLockPosY() const { return lockPosY; };
		bool GetLockPosZ() const { return lockPosZ; };
		bool GetLockRotX() const { return lockRotX; };
		bool GetLockRotY() const { return lockRotY; };
		bool GetLockRotZ() const { return lockRotZ; };
		void SetVelocity(const Math::Vector3& p_vel) { if (isStatic) { return; } rigidBody->setLinearVelocity(Wrapper::Physic::ToPxVec3(p_vel)); };
		Math::Vector3 GetVelocity() { if (isStatic) { return Math::Vector3(); } return Wrapper::Physic::ToVector3(rigidBody->getLinearVelocity()); };

	protected:
		void SetCollisionShapeAndType();

		MonoBehavior_Physics_Collider_GENERATED
	};
}
File_Collider_GENERATED