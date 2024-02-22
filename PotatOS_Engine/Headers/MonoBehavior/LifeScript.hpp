#pragma once

#include <MonoBehavior/IComponent.hpp>
#include <DLLInclude.hpp>
#include <MonoBehavior/Canva.hpp>

namespace MonoBehavior
{
	class POTATOS_ENGINE_API LifeScript : public IComponent
	{
		// Attributes
	private:
		int maxLife;
		int life;
		bool invinsible;
		float timer;
		float invinsibleTime;
		bool tookDamage;

		// Methods
	public:
		void Start(GAMESTATE* p_gameState) override;
		void Update(const float p_deltaTime, const Inputs& p_inputs) override;

		void SetMaxLife(const int p_max) { life = maxLife = p_max; };

		void TakeDamage(int p_damage);
		void ResetLife() { life = maxLife; };

		bool IsAlive() { return life > 0; }
		bool& GetTookDamage() { return tookDamage; };

		int GetLifePoints() { return life; };
	};
}
