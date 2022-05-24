/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE
 */
#pragma once

#include "AppGUI/Windows/BaseWindow.h"
#include "AppGUI/Core.h"
#include "AppGUI/Graphics/Graphics.h"
#include "AppGUI/Application.h"

namespace AppGUI {

	class GUI_API Window2D : public BaseWindow
	{
	private:
		bool isMain;

		Graphics* graphics;

		int m_width;
		int m_height;
	public:
		Window2D(HWND _hWndParent, bool _isMain = false);
		~Window2D();
		
 		bool Create(int x, int y, int width, int height) { return Create(x, y, width, height, NULL, NULL); }
		bool Create(int x, int y, int width, int height, DWORD dwStyle) { return Create(x, y, width, height, dwStyle, NULL); }
		bool Create(int x, int y, int width, int height, DWORD dwStyle, DWORD dwExStyle);

		bool Init();

		bool Show(int nCmdShow) {
			return ShowWindow(m_hWnd, nCmdShow);
		}

		LRESULT HandleProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

		void Update();
		void Render();
	};
}

