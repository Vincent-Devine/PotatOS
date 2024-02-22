#pragma once

#include <MonoBehavior/IComponent.hpp>
#include "MonoBehavior/Animator.hpp"
#include <DLLInclude.hpp>
#include <MonoBehavior/PlayerAttack.hpp>
#include <MonoBehavior/LifeScript.hpp>
#include <MonoBehavior/Physics/Collider.hpp>

namespace DataStructure::Animation
{
	class Animation;
}

namespace MonoBehavior
{
	class POTATOS_ENGINE_API TransitionScript : public IComponent
	{
		// Attributes
	private:
		Physics::Collider* collider;

		Animator* animator;
		float time;

		bool getAnimationData;

		bool replayAnimation;
		float timeReplayAnimation;

		bool transitionAlreadyPlay;

		DataStructure::Animation::Animation* animationWalk;
		DataStructure::Animation::Animation* animationIdle;
		DataStructure::Animation::Animation* animationAttack;
		DataStructure::Animation::Animation* animationHit;

		PlayerAttack* playerAttack = nullptr;
		LifeScript* lifeScript = nullptr;

		// Methods
	public:
		void Start(GAMESTATE* p_gameState) override;
		void Update(const float p_deltaTime, const Inputs& p_inputs) override;

	private:
		bool PtrCheck();
	};
}
