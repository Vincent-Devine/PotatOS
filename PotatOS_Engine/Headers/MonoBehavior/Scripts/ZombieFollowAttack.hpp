#pragma once
#include <DLLInclude.hpp>
#include <MonoBehavior/IComponent.hpp>
#include <MonoBehavior/LifeScript.hpp>

namespace MonoBehavior
{
	namespace Physics
	{
		class Collider;
	}

	namespace Script
	{
		class ZombieFollowAttack : public IComponent
		{
		private:
			DataStructure::Transform* transform = nullptr;
			DataStructure::Transform* playerTransform = nullptr;
			Physics::Collider* col = nullptr;
			MonoBehavior::LifeScript* lifeScript = nullptr;
			MonoBehavior::LifeScript* playerLifeScript = nullptr;

			float speed;
			float smellingRange;
			float attackRange;
			float minRange;
			float timer;
			float attackReloadTime;
			int attackDamage;

		public:
			bool followPlayer;
			bool playerRangeAttack;

		public:
			void Start(GAMESTATE* p_state) override;
			void Update(const float p_deltaTime, const Inputs& p_inputs) override;

		private:
			bool PtrCheck();
		};
	}
}