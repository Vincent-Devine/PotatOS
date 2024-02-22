#pragma once

#include <Wrapper/RHI.hpp>
#include "Guizmo.hpp"

namespace UI
{
	class Viewport
	{
	private:
		std::vector<float> fpsHistory;
		float fps;
		const int maxHistorySize = 100;

		// Methods
	public:
		void Draw(Wrapper::RHI& p_rhi, Guizmo& p_guizmo, DataStructure::GameObject* p_gameObjectSelected, Math::Vector2& windowSize);
	};
}
