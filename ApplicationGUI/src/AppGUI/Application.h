#pragma once

#include "Core.h"

namespace AppGUI {
	class GUI_API Application
	{
	public:
		//Application();
		//virtual ~Application();

		void Run();

	};
	
	// To be defined in client
	Application* CreateApplication();
}