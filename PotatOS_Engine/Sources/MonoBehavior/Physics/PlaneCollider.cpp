#include "pch.h"
#include <MonoBehavior/Physics/PlaneCollider.hpp>
#include <Core/ResourceManager.hpp>

namespace MonoBehavior::Physics
{
	PlaneCollider::PlaneCollider(const bool p_trigger, const bool p_queryShape):
		Collider(true, p_trigger, p_queryShape)
	{
		componentType = PLANE_COLLIDER;
		pMesh = Core::ResourceManager::Get()->UsePrimitiveMesh("Plane");
		pMesh->type = Resource::COLLIDER_TYPE::PLANE;
	}

	void PlaneCollider::Start(GAMESTATE* p_gameState)
	{
		Collider::Start(p_gameState);

		shape = physic->CreateShape(physx::PxPlaneGeometry(), isTrigger, queryable);

		physx::PxQuat rotation = physx::PxTransformFromPlaneEquation(physx::PxPlane(physx::PxVec3(0.f, 1.f, 0.f), 0.f)).q;
		tilt = Math::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
		
		SetCollisionShapeAndType();
	}
}