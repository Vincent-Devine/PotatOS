#include "pch.h"
#include <MonoBehavior/TransitionScript.hpp>
#include <MonoBehavior/Animator.hpp>
#include <Core/AnimationManager.hpp>
#include <Core/ResourceManager.hpp>
#include <MonoBehavior/Scripts/MenuScript.hpp>

namespace MonoBehavior
{
	void TransitionScript::Start(GAMESTATE* p_gameState)
	{
		componentType = SCRIPT;
		gameState = p_gameState;
		time = 0.f;
		transitionAlreadyPlay = false;
		replayAnimation = false;
		getAnimationData = false;
		animator = gameObject->GetAnimator();
		collider = gameObject->GetCollider();
	}

	void TransitionScript::Update(const float p_deltaTime, const Inputs& p_inputs)
	{

		if (!PtrCheck() || !lifeScript->IsAlive() || Script::MenuScript::showMenu)
		{
			return;
		}

		if (*gameState == GAMESTATE::EDIT)
		{
			if (!getAnimationData && Core::ResourceManager::Get()->UseMesh("Resources/Model/Michelle/Walking.dae")->GetIsFinishToInit())
			{
				DataStructure::Animation::Rig* rigPlayer = Core::AnimationManager::Get()->UseRig("Resources/Model/Michelle/Walking.dae");
				animationWalk = Core::AnimationManager::Get()->UseAnimation("Resources/Model/Michelle/Walking.dae", rigPlayer);
				animationAttack = Core::AnimationManager::Get()->UseAnimation("Resources/Model/Michelle/Kick.dae", rigPlayer);
				animationHit = Core::AnimationManager::Get()->UseAnimation("Resources/Model/Michelle/Head_Hit.dae", rigPlayer);
				animationIdle = Core::AnimationManager::Get()->UseAnimation("Resources/Model/Michelle/Idle.dae", rigPlayer);
				animator->PlayAnimation(animationIdle);
				getAnimationData = true;
			}
			gameObject->transform.SetScale(Math::Vector3(.025f, .025f, .025f));
		}
		else
		{
			animator->SetSpeed(2.f);

			if (!(p_inputs.moveForward || p_inputs.moveBackward || p_inputs.moveLeft || p_inputs.moveRight) 
				&& animator->GetCurrentAnimation()->GetPath() != animationIdle->GetPath()
				&& !transitionAlreadyPlay)
			{
				animator->StartTransition(animationIdle, 0.2f);
				timeReplayAnimation = time + 0.3f;
				replayAnimation = true;
				transitionAlreadyPlay = true;
			}
			else if((p_inputs.moveForward || p_inputs.moveBackward || p_inputs.moveLeft || p_inputs.moveRight)
				&& !transitionAlreadyPlay && animator->GetCurrentAnimation()->GetPath() != animationWalk->GetPath())
			{
				animator->StartTransition(animationWalk, 0.2f);
				timeReplayAnimation = time + 0.3f;
				replayAnimation = true;
				transitionAlreadyPlay = true;
			}

			if (!transitionAlreadyPlay && lifeScript->GetTookDamage())
			{
				animator->StartTransition(animationHit, 0.001f);
				timeReplayAnimation = time + animationHit->GetDuration();
				transitionAlreadyPlay = true;
				replayAnimation = true;
			}

			if (!transitionAlreadyPlay && p_inputs.attack)
			{
				animator->SetSpeed(2.f);
				animator->StartTransition(animationAttack, 0.1f);
				timeReplayAnimation = time + animationAttack->GetDuration();
				transitionAlreadyPlay = true;
				replayAnimation = true;
				playerAttack->SetIsAttack(true);
			}

			if (replayAnimation && timeReplayAnimation <= time)
			{
				if (animator->GetCurrentAnimation()->GetPath() != animationWalk->GetPath() && animator->GetCurrentAnimation()->GetPath() != animationIdle->GetPath())
				{
					animator->StartTransition(animationWalk, 0.01f);
				}
				replayAnimation = false;
				transitionAlreadyPlay = false;
				playerAttack->SetIsAttack(false);
			}

			time += p_deltaTime;
			gameObject->transform.SetScale(Math::Vector3(2.5f, 2.5f, 2.5f));
		}
	}

	bool TransitionScript::PtrCheck()
	{
		if (!playerAttack)
		{
			playerAttack = gameObject->GetComponent<PlayerAttack>();
		}

		if (!lifeScript)
		{
			lifeScript = gameObject->GetComponent<LifeScript>();
		}

		return playerAttack && lifeScript;
	}
}