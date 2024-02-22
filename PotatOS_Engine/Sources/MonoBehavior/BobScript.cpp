#include "pch.h"
#include <MonoBehavior/BobScript.hpp>
#include <MonoBehavior/Animator.hpp>
#include <Core/AnimationManager.hpp>
#include <Core/ResourceManager.hpp>
#include <MonoBehavior/Physics/Collider.hpp>

namespace MonoBehavior
{
	void BobScript::Start(GAMESTATE* p_gameState)
	{
		componentType = SCRIPT;
		gameState = p_gameState;
		getAnimationData = false;
		replayAnimation = false;
		transitionAlreadyPlay = false;
		for (unsigned int i = 0; i < gameObject->components.size(); i++)
		{
			life = dynamic_cast<LifeScript*>(gameObject->components[i]);
			if (life)
			{
				playDeathAnimation = false;
				break;
			}
		}
		zombieFollowScript = gameObject->GetComponent<Script::ZombieFollowAttack>();
		zombieSoundScript = gameObject->GetComponent<Script::PlaySoundEnemyScript>();
	}

	void BobScript::Update(const float p_deltaTime, const Inputs& p_inputs)
	{
		if (*gameState == GAMESTATE::EDIT)
		{
			animator = gameObject->GetAnimator();
			if (!getAnimationData && Core::ResourceManager::Get()->UseMesh("Resources/Model/Zombie/Walking.dae")->GetIsFinishToInit())
			{
				DataStructure::Animation::Rig* zombieRig = Core::AnimationManager::Get()->UseRig("Resources/Model/Zombie/Walking.dae");
				walking = Core::AnimationManager::Get()->UseAnimation("Resources/Model/Zombie/Walking.dae", zombieRig);
				dying = Core::AnimationManager::Get()->UseAnimation("Resources/Model/Zombie/Dying.dae", zombieRig);
				hit = Core::AnimationManager::Get()->UseAnimation("Resources/Model/Zombie/Hit.dae", zombieRig);
				attack = Core::AnimationManager::Get()->UseAnimation("Resources/Model/Zombie/Attack.dae", zombieRig);
				idle = Core::AnimationManager::Get()->UseAnimation("Resources/Model/Zombie/Idle.dae", zombieRig);

				animator->PlayAnimation(walking);
				gameObject->transform.SetScale(Math::Vector3(.025f, .025f, .025f));
				getAnimationData = true;
			}

			if (!playerLifeScript)
			{
				playerLifeScript = gameObject->Find("Player")->GetComponent<LifeScript>();
			}

			for (unsigned int i = 0; i < gameObject->components.size(); i++)
			{
				Physics::Collider* collider = dynamic_cast<Physics::Collider*>(gameObject->components[i]);
				if (collider)
				{
					collider->SetIsActive(true);
					break;
				}
			}
			if (!life->IsAlive())
			{
				Reset();
			}
			animator->SetSpeed(2.f);
		}
		else
		{
			gameObject->transform.SetScale(Math::Vector3(2.5f, 2.5f, 2.5f));
			if (!playDeathAnimation && !life->IsAlive())
			{
				animator->StartTransition(dying, 1.f);
				playDeathAnimation = true;
				animator->SetLoop(true);
				for (unsigned int i = 0; i < gameObject->components.size(); i++)
				{
					Physics::Collider* collider = dynamic_cast<Physics::Collider*>(gameObject->components[i]);
					if (collider)
					{
						collider->SetIsActive(false);
						return;
					}
				}
			}

			if (!life->IsAlive())
			{
				return;
			}

			if (!zombieFollowScript->followPlayer && animator->GetCurrentAnimation()->GetPath() != idle->GetPath() && !transitionAlreadyPlay)
			{
				animator->StartTransition(idle, 0.2f);
				timeReplayAnimation = time + 0.3f;
				replayAnimation = true;
				transitionAlreadyPlay = true;
			}
			else if (zombieFollowScript->followPlayer && animator->GetCurrentAnimation()->GetPath() != walking->GetPath() && !transitionAlreadyPlay)
			{
				animator->StartTransition(walking, 0.2f);
				timeReplayAnimation = time + 0.3f;
				replayAnimation = true;
				transitionAlreadyPlay = true;
			}

			if (life->GetTookDamage())
			{
				animator->StartTransition(hit, 0.1f);
				timeReplayAnimation = time + hit->GetDuration();
				replayAnimation = true;
				transitionAlreadyPlay = true;
			}

			if (playerLifeScript && playerLifeScript->GetTookDamage() && zombieFollowScript->playerRangeAttack)
			{
				animator->StartTransition(attack, 0.1f);
				timeReplayAnimation = time + attack->GetDuration();
				replayAnimation = true;
				transitionAlreadyPlay = true;
				zombieSoundScript->playEnemySound = true;
			}

			if (replayAnimation && timeReplayAnimation <= time)
			{
				if (animator->GetCurrentAnimation()->GetPath() != walking->GetPath() && animator->GetCurrentAnimation()->GetPath() != idle->GetPath())
				{
					animator->StartTransition(walking, 0.1f);
				}
				replayAnimation = false;
				transitionAlreadyPlay = false;
			}

			time += p_deltaTime;
		}
	}

	void BobScript::Reset()
	{
		playDeathAnimation = false;
		life->ResetLife();
		gameObject->GetAnimator()->SetLoop(false);
		gameObject->GetAnimator()->PlayAnimation(walking);
	}
}