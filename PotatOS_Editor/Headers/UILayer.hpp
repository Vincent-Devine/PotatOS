#pragma once

#include <Wrapper/Window.hpp>

namespace Wrapper
{
	class UILayer
	{
	//Attributes
	private:
		bool firstFrame = true;
		
		// Methods
	public:
		void Init(Window& p_window);
		void Update();
		void Draw() const;
		void Destroy();

	private:
		void SetDocking(const char* p_windowName);
	};
}
