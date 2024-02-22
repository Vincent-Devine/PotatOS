#pragma once

#include <MonoBehavior/IComponent.hpp>
#include <DLLInclude.hpp>
#include <MonoBehavior/LifeScript.hpp>
#include <MonoBehavior/Animator.hpp>
#include <MonoBehavior/Scripts/ZombieFollowAttack.hpp>
#include <MonoBehavior/Scripts/PlaySoundEnemyScript.hpp>

namespace DataStructure::Animation
{
	class Animation;
}

namespace MonoBehavior
{
	class POTATOS_ENGINE_API BobScript : public IComponent
	{
		// Attribute
	private:
		bool getAnimationData;
		LifeScript* life;
		bool playDeathAnimation;
		float time;
		float timeReplayAnimation;
		bool transitionAlreadyPlay;
		bool replayAnimation;
		Animator* animator;

		DataStructure::Animation::Animation* walking;
		DataStructure::Animation::Animation* dying;
		DataStructure::Animation::Animation* hit;
		DataStructure::Animation::Animation* attack;
		DataStructure::Animation::Animation* idle;
		Script::ZombieFollowAttack* zombieFollowScript;
		Script::PlaySoundEnemyScript* zombieSoundScript;

		LifeScript* playerLifeScript = nullptr;

		// Methods
	public:
		void Start(GAMESTATE* p_gameState) override;
		void Update(const float p_deltaTime, const Inputs& p_inputs) override;
		void Reset();
	};
}
