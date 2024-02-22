#include "pch.h"
#include <MonoBehavior/Physics/SphereCollider.hpp>
#include <Core/ResourceManager.hpp>

namespace MonoBehavior::Physics
{
	SphereCollider::SphereCollider(const float p_radius, const bool p_static, const bool p_trigger, const bool p_queryShape, const Math::Vector3& p_offset):
		Collider(p_static, p_trigger, p_queryShape, p_offset),
		radius(p_radius)
	{
		componentType = SPHERE_COLLIDER;
		pMesh = Core::ResourceManager::Get()->UsePrimitiveMesh("Sphere");
		pMesh->type = Resource::COLLIDER_TYPE::SPHERE;
		transform.SetScale(Math::Vector3::One() * p_radius);
	}

	void SphereCollider::Start(GAMESTATE* p_gameState)
	{
		Collider::Start(p_gameState);

		shape = physic->CreateShape(physx::PxSphereGeometry(radius), isTrigger, queryable);

		SetCollisionShapeAndType();
	}

	void SphereCollider::SetRadius()
	{
		transform.SetScale(Math::Vector3::One() * radius);
		physx::PxSphereGeometry sphereGeometry;
		shape->getSphereGeometry(sphereGeometry);
		sphereGeometry.radius = radius;
		shape->setGeometry(sphereGeometry);
	}
}