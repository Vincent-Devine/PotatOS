#include "pch.h"
#include <MonoBehavior/Physics/BoxCollider.hpp>
#include <Core/ResourceManager.hpp>

namespace MonoBehavior::Physics
{
	BoxCollider::BoxCollider(const Math::Vector3& p_scale, const bool p_static, const bool p_trigger, const bool p_queryShape, const Math::Vector3& p_offset):
		Collider(p_static, p_trigger, p_queryShape, p_offset),
		scale(p_scale)
	{
		componentType = BOX_COLLIDER;
		pMesh = Core::ResourceManager::Get()->UsePrimitiveMesh("Box");
		pMesh->type = Resource::COLLIDER_TYPE::BOX;
		transform.SetScale(p_scale);
	}

	void BoxCollider::Start(GAMESTATE* p_gameState)
	{
		Collider::Start(p_gameState);

		shape = physic->CreateShape(physx::PxBoxGeometry(scale.x, scale.y, scale.z), isTrigger, queryable);

		SetCollisionShapeAndType();
	}

	void BoxCollider::SetScale()
	{
		transform.SetScale(scale);
		physx::PxBoxGeometry boxGeometry;
		shape->getBoxGeometry(boxGeometry);
		boxGeometry.halfExtents = Wrapper::Physic::ToPxVec3(scale);
		shape->setGeometry(boxGeometry);
	}
}