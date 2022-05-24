/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE
 */
#pragma once

#include "Core.h"
#include "pch.h"
#include "Windows/Window2D.h"

namespace AppGUI {
	
	enum MessageBoxType {
		MessageBox_Ok = MB_OK
	};

	class GUI_API Window2D;
	
	class GUI_API Application
	{
	private:
		std::vector<Window2D*> windowList;

		static Application* instance;
	public:
		Application();
		virtual ~Application();

		static Application* getInstance();

		void Run();

		void UnregisterWindow(Window2D*);

		void ShowMessage(wchar_t const* title, wchar_t const* text, UINT type) {
			MessageBox(nullptr, text, title, type);
		}
	};
	
	// To be defined in client
	Application* CreateApplication();
	

}
