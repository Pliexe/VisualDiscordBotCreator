/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE
 */
#include "Application.h"
#include "pch.h"

namespace AppGUI {

	void Application::UnregisterWindow(Window2D* window) {
		windowList.erase(std::remove_if(windowList.begin(), windowList.end(), [window](Window2D* pred) { return pred == window; }), windowList.end());
	}
	
	Application::Application() {
		if (instance != nullptr) {
			MessageBox(NULL, L"Cant create multiple of application in application.", L"Error", MB_ICONERROR);
			throw -250;
		} else instance = this;
	}
	
	Application::~Application() {
		//for (Window2D* win : windowList)
		//	if(win != nullptr) delete win;
	}

	Application* Application::instance;
	
	Application* Application::getInstance()
	{
		return instance;
	}
	
	void Application::Run()
	{		
		Window2D* mainWindow = new Window2D(NULL, true);

		windowList.push_back(mainWindow);

		if (!mainWindow->Create(0, 0, 800, 600, WS_OVERLAPPEDWINDOW)) {
			ShowMessage(L"Error", L"Could not create window", MB_ICONERROR);
			return;
		}

		if (!mainWindow->Init())
		{
			ShowMessage(L"Error", L"Failed to create Direct 2D target.", MB_ICONERROR);
			return;
		}

		mainWindow->Show(SW_SHOWMAXIMIZED);


		for (int i = 0; i < 3; i++)
		{
			//Window2D* sideWindow = new Window2D(mainWindow->m_hWnd);
			Window2D* sideWindow = new Window2D(NULL);

			
			windowList.push_back(sideWindow);

			if (!sideWindow->Create(0, 0, 800, 600, WS_POPUP | WS_CLIPSIBLINGS, NULL)) {
				ShowMessage(L"Error", L"Could not create window", MB_ICONERROR);
				return;
			}

			// Windows 11 Styling
			DWM_WINDOW_CORNER_PREFERENCE prefrence = DWMWCP_ROUND;
			DwmSetWindowAttribute(sideWindow->m_hWnd, DWMWA_WINDOW_CORNER_PREFERENCE, &prefrence, sizeof(prefrence));

			/*SetWindowLong(sideWindow->m_hWnd, GWL_STYLE, 0);
			SetWindowPos(sideWindow->m_hWnd, 0, 150, 100, 250, 250, SWP_FRAMECHANGED);*/

			if (!sideWindow->Init())
			{
				ShowMessage(L"Error", L"Failed to create Direct 2D target.", MB_ICONERROR);
				return;
			}

			sideWindow->Show(SW_SHOW);
		}

		MSG message;
		message.message = WM_NULL;
		
		while (message.message != WM_QUIT) {
			if(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&message);
				DispatchMessage(&message);
			} else {
				for (std::vector<Window2D*>::iterator it = windowList.begin(), end = windowList.end(); it != end; ++it)
				{
					(*it)->Update();
					(*it)->Render();
				}
				Sleep(10);
			}
		}
	}
}