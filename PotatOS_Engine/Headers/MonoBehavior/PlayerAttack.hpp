#pragma once

#include <MonoBehavior/Scripts/PlaySoundScript.hpp>

namespace MonoBehavior
{
	class POTATOS_ENGINE_API PlayerAttack : public Script::BaseScript
	{
		// Attribute
	private:
		float speedInAttack;
		bool isAttacking;

		Script::PlaySoundScript * playSoundScript;
		// Methods
	public:
		void Start(GAMESTATE* p_gameState) override;

		const float GetSpeedInAttack() { return speedInAttack; };
		const bool GetIsAttacking() { return isAttacking; };

		void SetIsAttack(const bool p_isAttacking) { isAttacking = p_isAttacking; };
	};
}