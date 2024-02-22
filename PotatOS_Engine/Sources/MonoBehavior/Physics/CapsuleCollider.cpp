#include "pch.h"
#include <MonoBehavior/Physics/CapsuleCollider.hpp>
#include <Core/ResourceManager.hpp>

namespace MonoBehavior::Physics
{
	CapsuleCollider::CapsuleCollider(const float p_radius, const AXIS_ALIGNMENT p_alignment, const float p_halfHeight, const bool p_static, const bool p_trigger, const bool p_queryShape, const Math::Vector3& p_offset):
		Collider(p_static, p_trigger, p_queryShape, p_offset),
		radius(p_radius),
		alignment(p_alignment),
		halfHeight(p_halfHeight)
	{
		componentType = CAPSULE_COLLIDER;
		pMesh = Core::ResourceManager::Get()->UsePrimitiveMesh("Capsule");
		pMesh->type = Resource::COLLIDER_TYPE::CAPSULE;
	}

	void CapsuleCollider::SetTilt()
	{
		switch (alignment)
		{
		case MonoBehavior::Physics::AXIS_ALIGNMENT::Y:
			tilt = Math::Quaternion::QuatFromEuler(0.f, 0.f, 90.f);
			break;
		case MonoBehavior::Physics::AXIS_ALIGNMENT::Z:
			tilt = Math::Quaternion::QuatFromEuler(0.f, 90.f, 0.f);
			break;
		default:
			tilt = Math::Quaternion::Identity();
			break;
		}
	}

	void CapsuleCollider::Start(GAMESTATE* p_gameState)
	{
		Collider::Start(p_gameState);

		shape = physic->CreateShape(physx::PxCapsuleGeometry(radius, halfHeight), isTrigger, queryable);

		SetTilt();

		pMesh->InitCapsule(halfHeight, radius);

		SetCollisionShapeAndType();
	}

	void CapsuleCollider::SetAlignment(int p_alignment)
	{
		alignment = (AXIS_ALIGNMENT)p_alignment;
		SetTilt();
		modified = true;
		gameObject->transform.Update();
	}

	void CapsuleCollider::SetRadius()
	{
		pMesh->InitCapsule(halfHeight, radius);
		if (!isStatic)
		{
			rigidBody->wakeUp();
		}
		physx::PxCapsuleGeometry capsuleGeometry;
		shape->getCapsuleGeometry(capsuleGeometry);
		capsuleGeometry.radius = radius;
		shape->setGeometry(capsuleGeometry);
	}

	void CapsuleCollider::SetHalfHeight()
	{
		pMesh->InitCapsule(halfHeight, radius);
		if (!isStatic)
		{
			rigidBody->wakeUp();
		}
		physx::PxCapsuleGeometry capsuleGeometry;
		shape->getCapsuleGeometry(capsuleGeometry);
		capsuleGeometry.halfHeight = halfHeight;
		shape->setGeometry(capsuleGeometry);
	}
}