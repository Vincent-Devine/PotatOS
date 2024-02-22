#include "pch.h"

#include <MonoBehavior/Physics/Collider.hpp>
#include <DebugSystem/Log.hpp>
#include <DebugSystem/Assertion.hpp>
#include <Core/ResourceManager.hpp>

namespace MonoBehavior::Physics
{
	Collider::Collider(const bool p_static, const bool p_trigger, const bool p_queryShape, const Math::Vector3& p_offset):
		isTrigger(p_trigger),
		queryable(p_queryShape),
		isStatic(p_static),
		offset(p_offset)
	{
		Core::ResourceManager* rsrcMngr = Core::ResourceManager::Get();
		shader = rsrcMngr->UseShader("Resources/Shaders/Collider.vert", "Resources/Shaders/Collider.frag");
		physic = Wrapper::Physic::Get();
		transform.SetPosition(p_offset);
		modified = true;
	}

	void Collider::Start(GAMESTATE* p_gameState)
	{
		gameState = p_gameState;
		transform.parentTransform = &gameObject->transform;
		transform.parentTransform->Update();
		transform.Update();
	}

	void Collider::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (!isStatic && *gameState == GAMESTATE::EDIT)
		{
			rigidBody->setLinearVelocity(physx::PxVec3(0.f, 0.f, 0.f));
			rigidBody->setAngularVelocity(physx::PxVec3(0.f, 0.f, 0.f));
		}

		transform.SetPosition(Wrapper::Physic::ToVector3(baseActor->getGlobalPose().p));
		transform.SetRotation(Wrapper::Physic::ToQuaternion(baseActor->getGlobalPose().q));
		Math::Mat4 offsetMat = Math::Quaternion::QuatToMatrix(gameObject->transform.GetLocalRotation()) * Math::Mat4::CreateTranslationMatrix(-offset);
		anti = Math::Vector3(offsetMat.data[0][3], offsetMat.data[1][3], offsetMat.data[2][3]);
		
		if (*gameState == GAMESTATE::PLAY)
		{
			AxisLock();
		}

		if (modified || isStatic)
		{
			baseActor->setGlobalPose(physx::PxTransform(Wrapper::Physic::ToPxVec3(gameObject->transform.GetPosition() - anti), Wrapper::Physic::ToPxQuat(gameObject->transform.GetRotation() * tilt)));
			modified = false;
		}
		else
		{
			gameObject->transform.SetRotation(transform.GetLocalRotation() * tilt.Invert());
			gameObject->transform.SetPosition(transform.GetLocalPosition() + anti);
		}
		transform.Update();

	}

	void Collider::Draw(const MonoBehavior::Renderer::Camera* p_camera, const DataStructure::LightManager& p_lightManager, const MonoBehavior::Renderer::Light* p_light) const
	{
		if (!gameObject->IsSelected())
		{
			return;
		}
		shader->Use();
		Math::Mat4 model = Math::Mat4::CreateTransformationMatrix(gameObject->transform.GetPosition() - anti, transform.GetLocalScale(), transform.GetLocalRotation());

		shader->SetMat4("mvp", p_camera->GetProjection() * p_camera->GetView() * model);

		pMesh->Draw(*shader->GetShaderProgram());
	}

	void Collider::Destroy()
	{
		Core::ResourceManager* resourceManager = Core::ResourceManager::Get();

		resourceManager->StopUsedResource(shader);
		resourceManager->StopUsedResource(pMesh);
		if (staticBody)
		{
			if (!staticBody->isReleasable())
			{
				Log::Print("static collider can not be released", LOG_LEVEL_TYPE::Warning);
			}
			else
			{
				staticBody->release();
				staticBody = nullptr;
			}
		}
		if (rigidBody)
		{
			if (!rigidBody->isReleasable())
			{
				Log::Print("rigid body can not be released", LOG_LEVEL_TYPE::Warning);
			}
			else
			{
				rigidBody->release();
				rigidBody = nullptr;
			}
		}
	}

	void Collider::AxisLock()
	{
		if (isStatic)
		{
			return;
		}

		physx::PxVec3 lVel = rigidBody->getLinearVelocity();
		physx::PxVec3 aVel = rigidBody->getAngularVelocity();
		if (lockPosX)
		{
			lVel.x = 0.f;
		}
		if (lockPosY)
		{
			lVel.y = 0.f;
		}
		if (lockPosZ)
		{
			lVel.z = 0.f;
		}
		if (lockRotX)
		{
			aVel.x = 0.f;
		}
		if (lockRotY)
		{
			aVel.y = 0.f;
		}
		if (lockRotZ)
		{
			aVel.z = 0.f;
		}
		rigidBody->setLinearVelocity(lVel);
		rigidBody->setAngularVelocity(aVel);
	}

	void Collider::AddForce(const Math::Vector3& p_force, const bool p_isImpulse)
	{
		if (isStatic || !rigidBody)
		{
			return;
		}
		rigidBody->addForce(Wrapper::Physic::ToPxVec3(p_force), p_isImpulse ? physx::PxForceMode::eIMPULSE : physx::PxForceMode::eFORCE);
	}

	void Collider::SetCollisionShapeAndType()
	{
		physx::PxTransform pxtransform = physx::PxTransform(Wrapper::Physic::ToPxVec3(transform.GetPosition()), Wrapper::Physic::ToPxQuat(transform.GetRotation()));

		if (isStatic)
		{
			staticBody = physic->CreateRigidStatic(pxtransform);
			staticBody->attachShape(*shape);
			physic->AddActor(staticBody);
			baseActor = static_cast<physx::PxRigidActor*>(staticBody);
		}
		else
		{
			rigidBody = physic->CreateRigidDynamic(pxtransform);
			rigidBody->attachShape(*shape);
			physic->AddActor(rigidBody);
			baseActor = static_cast<physx::PxRigidActor*>(rigidBody);
		}
		baseActor->userData = this;

		AxisLock();
	}

	void Collider::ToggleStatic()
	{
		if (isStatic)
		{
			staticBody = physic->CreateRigidStatic(baseActor->getGlobalPose());
			baseActor->detachShape(*shape);
			staticBody->attachShape(*shape);
			physic->AddActor(staticBody);
			baseActor = static_cast<physx::PxRigidActor*>(staticBody);
			Assertion(rigidBody->isReleasable(), "Collider not releasable");
			rigidBody->release();
			rigidBody = nullptr;
		}
		else
		{
			rigidBody = physic->CreateRigidDynamic(baseActor->getGlobalPose());
			baseActor->detachShape(*shape);
			rigidBody->attachShape(*shape);
			physic->AddActor(rigidBody);
			baseActor = static_cast<physx::PxRigidActor*>(rigidBody);
			Assertion(staticBody->isReleasable(), "Collider not releasable");
			staticBody->release();
			staticBody = nullptr;
		}
		baseActor->userData = this;
	};

	void Collider::ToggleTrigger()
	{
		shape->setFlags(Wrapper::Physic::ShapeFlags(isTrigger, queryable));
	};

	void Collider::ToggleQueryable()
	{
		shape->setFlags(Wrapper::Physic::ShapeFlags(isTrigger, queryable));
	};
}
