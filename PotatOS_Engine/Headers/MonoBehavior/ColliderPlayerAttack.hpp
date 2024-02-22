#pragma once

#include <MonoBehavior/IComponent.hpp>
#include <DLLInclude.hpp>
#include <MonoBehavior/PlayerAttack.hpp>
#include <MonoBehavior/Physics/BoxCollider.hpp>

namespace MonoBehavior
{
	class LifeScript;

	class POTATOS_ENGINE_API ColliderPlayerAttack : public IComponent
	{
		// Attributes
	private:
		PlayerAttack* playerAttack = nullptr;
		Physics::BoxCollider* boxCollider = nullptr;

		// Methods
	public:
		void Start(GAMESTATE* p_gameState) override;
		void Update(const float p_deltaTime, const Inputs& p_inputs) override;

	private:
		bool PtrCheck();
	};
}
