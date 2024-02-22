#pragma once

#include <MonoBehavior/IComponent.hpp>
#include <Math/Vector3.hpp>

namespace MonoBehavior
{
	class MoveCameraEditor : public IComponent
	{
		// Attributes
	private:
		float* speed;
		Math::Vector3* rotation = nullptr;

		// Methods
	public:
		void Start(GAMESTATE* p_gameState) override;
		void Update(const float p_deltaTime, const Inputs& p_inputs) override;
	};
}
