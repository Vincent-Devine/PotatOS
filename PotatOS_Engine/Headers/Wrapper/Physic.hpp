#pragma once

#include <vector>

#include <PxPhysicsAPI.h>

#include <DataStructure/Transform.hpp>
#include <Math/Vector3.hpp>

namespace MonoBehavior::Physics
{
	class Collider;
}

struct RaycastHit
{
	bool hasBlock = false;
	Math::Vector3 position;
	Math::Vector3 normal;
	float distance = 0.f;
	DataStructure::GameObject* object = nullptr;
	MonoBehavior::Physics::Collider* collider = nullptr;
};

struct OverlapHit
{
	DataStructure::GameObject* object = nullptr;
	MonoBehavior::Physics::Collider* collider = nullptr;
};

namespace Wrapper
{

	class Physic
	{
	//Attributes
	private:
		static Physic* singleton;

		physx::PxDefaultAllocator allocator;
		physx::PxDefaultErrorCallback errorCallback;
		physx::PxFoundation* foundation = nullptr;
		physx::PxPhysics* physics = nullptr;
		physx::PxDefaultCpuDispatcher* dispatcher = nullptr;
		physx::PxScene* scene = nullptr;
		physx::PxMaterial* material = nullptr;

	//Methods
	public:
		static Physic* Get();

		void Init();
		void Update();
		void Step();
		void Cleanup();

		RaycastHit Raycast(const Math::Vector3 p_origin, const Math::Vector3 p_direction, const float p_maxDistance);
		std::vector<OverlapHit> Overlap(const MonoBehavior::Physics::Collider& p_collider);
		static physx::PxShapeFlags ShapeFlags(const bool p_trigger, bool p_queryShape);
		physx::PxShape* CreateShape(const physx::PxGeometry& p_geometry, const bool p_trigger, const bool p_queryShape);
		physx::PxRigidStatic* CreateRigidStatic(const physx::PxTransform& p_transform);
		physx::PxRigidDynamic* CreateRigidDynamic(const physx::PxTransform& p_transform);
		static physx::PxVec3 ToPxVec3(const Math::Vector3& p_vec);
		static physx::PxQuat ToPxQuat(const Math::Quaternion& p_quat);
		static Math::Vector3 ToVector3(const physx::PxVec3& p_vec);
		static Math::Quaternion ToQuaternion(const physx::PxQuat& p_quat);
		
		void AddActor(physx::PxActor* p_actor) { scene->addActor(*p_actor); };
	};
}