#include "pch.h"

#include <string>

#include <Wrapper/Physic.hpp>
#include <DebugSystem/Log.hpp>
#include <MonoBehavior/Physics/Collider.hpp>
#include <Wrapper/RHI.hpp>
#include <MonoBehavior/Renderer/Camera.hpp>
#include <DataStructure/LightManager.hpp>

namespace Wrapper
{
	Physic* Physic::singleton = nullptr;

	Physic* Physic::Get()
	{
		if (singleton == nullptr)
		{
			singleton = new Physic;
		}
		return singleton;
	}

	void Physic::Init()
	{
		foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);

		physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, physx::PxTolerancesScale(), true);

		physx::PxSceneDesc sceneDesc(physics->getTolerancesScale());
		sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
		dispatcher = physx::PxDefaultCpuDispatcherCreate(2);
		sceneDesc.cpuDispatcher = dispatcher;
		sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
		scene = physics->createScene(sceneDesc);

		material = physics->createMaterial(0.5f, 0.5f, 0.6f);
	}

	void Physic::Update()
	{
		Step();
	}

	void Physic::Step()
	{
		scene->simulate(1.0f / 60.0f);
		scene->fetchResults(true);
	}

	void Physic::Cleanup()
	{
		PX_RELEASE(scene);
		PX_RELEASE(dispatcher);
		PX_RELEASE(physics);
		PX_RELEASE(foundation);
	}

	RaycastHit Physic::Raycast(const Math::Vector3 p_origin, const Math::Vector3 p_direction, const float p_maxDistance)
	{
		physx::PxRaycastBuffer hit;
		const physx::PxHitFlags hitFlags = physx::PxHitFlag::ePOSITION | physx::PxHitFlag::eNORMAL | physx::PxHitFlag::eANY_HIT;
		scene->raycast(ToPxVec3(p_origin), ToPxVec3(p_direction), p_maxDistance, hit, hitFlags);
		if(!hit.hasBlock)
		{
			return RaycastHit{};
		}
		MonoBehavior::Physics::Collider* col = static_cast<MonoBehavior::Physics::Collider*>(hit.block.actor->userData);
		return RaycastHit
		{
			hit.hasBlock,
			ToVector3(hit.block.position),
			ToVector3(hit.block.normal),
			hit.block.distance,
			col->gameObject,
			col
		};
	}

	std::vector<OverlapHit> Physic::Overlap(const MonoBehavior::Physics::Collider& p_collider)
	{
		std::vector<OverlapHit> overlapedColliders;

		if (!p_collider.IsTrigger())
		{
			Log::Print("Not a trigger", LOG_LEVEL_TYPE::Warning);
			return overlapedColliders;
		}

		physx::PxOverlapBuffer hit;
		hit.maxNbTouches = 10U;
		hit.touches = new physx::PxOverlapHit[10U];
		physx::PxQueryFilterData filter;
		filter.flags = physx::PxQueryFlag::eNO_BLOCK | physx::PxQueryFlag::eDYNAMIC | physx::PxQueryFlag::eSTATIC;
		scene->overlap(p_collider.GetShape()->getGeometry(), physx::PxTransform(ToPxVec3(p_collider.gameObject->transform.GetPosition()), ToPxQuat(p_collider.gameObject->transform.GetRotation())), hit, filter);
		
		for (unsigned int i = 0U; i < hit.nbTouches; i++)
		{
			if (hit.touches[i].actor == p_collider.GetBaseActor())
			{
				continue;
			}

			MonoBehavior::Physics::Collider* col = static_cast<MonoBehavior::Physics::Collider*>(hit.touches[i].actor->userData);
			overlapedColliders.push_back(OverlapHit{ col->gameObject, col });
		}

		return overlapedColliders;
	}

	physx::PxShapeFlags Physic::ShapeFlags(const bool p_trigger, bool p_queryShape)
	{
		physx::PxShapeFlags shapeFlags = physx::PxShapeFlag::eVISUALIZATION;

		if (p_queryShape)
		{
			shapeFlags = shapeFlags | physx::PxShapeFlag::eSCENE_QUERY_SHAPE;
		}

		if (p_trigger)
		{
			shapeFlags = shapeFlags | physx::PxShapeFlag::eTRIGGER_SHAPE;
		}
		else
		{
			shapeFlags = shapeFlags | physx::PxShapeFlag::eSIMULATION_SHAPE;
		}

		return shapeFlags;
	}

	physx::PxShape* Physic::CreateShape(const physx::PxGeometry& p_geometry, const bool p_trigger, const bool p_queryShape)
	{
		return physics->createShape(p_geometry, &material, 1, true, ShapeFlags(p_trigger, p_queryShape));
	}

	physx::PxRigidStatic* Physic::CreateRigidStatic(const physx::PxTransform& p_transform)
	{
		return physics->createRigidStatic(p_transform);
	}

	physx::PxRigidDynamic* Physic::CreateRigidDynamic(const physx::PxTransform& p_transform)
	{
		return physics->createRigidDynamic(p_transform);
	}

	physx::PxVec3 Physic::ToPxVec3(const Math::Vector3& p_vec)
	{
		return physx::PxVec3(p_vec.x, p_vec.y, p_vec.z);
	}

	physx::PxQuat Physic::ToPxQuat(const Math::Quaternion& p_quat)
	{
		return physx::PxQuat(p_quat.x, p_quat.y, p_quat.z, p_quat.w);
	}

	Math::Vector3 Physic::ToVector3(const physx::PxVec3& p_vec)
	{
		return Math::Vector3(p_vec.x, p_vec.y, p_vec.z);
	}

	Math::Quaternion Physic::ToQuaternion(const physx::PxQuat& p_quat)
	{
		return Math::Quaternion(p_quat.x, p_quat.y, p_quat.z, p_quat.w);
	}
}