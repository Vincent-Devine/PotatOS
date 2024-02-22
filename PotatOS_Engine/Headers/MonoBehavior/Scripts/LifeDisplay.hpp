#pragma once
#include <DLLInclude.hpp>
#include <MonoBehavior/IComponent.hpp>
#include <MonoBehavior/Canva.hpp>
#include <MonoBehavior/LifeScript.hpp>

namespace MonoBehavior::Script
{
	class LifeDisplay : public IComponent
	{
	public:
		static bool gameOver;

	private:
		Canva* canva = nullptr;
		LifeScript* playerLifeScript = nullptr;
		MonoBehavior::Physics::Collider* finishCollider = nullptr;

	public:
		void Update(const float p_deltaTime, const Inputs& p_inputs) override;

	private:
		bool CheckWin();
		bool PtrCheck();
	};
}