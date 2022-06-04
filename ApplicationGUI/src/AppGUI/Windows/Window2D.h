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

		int m_x;

		bool maximized = false;

		ID2D1SolidColorBrush* titleBarBrush;
		//ID2D1SolidColorBrush* titleBarTextBrush;
		ID2D1SolidColorBrush* titleBarIconBrush;

		IDWriteTextFormat* textFormat;

		void RenderTitleBar();

	public:
		Window2D(HWND _hWndParent, bool _isMain = false);
		~Window2D();
		
		bool Create(int x, int y, int width, int height);

		bool Init();

		bool Show() {
			return ShowWindow(m_hWnd, SW_SHOW);
		}

		LRESULT HandleProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

		void Update();
		void Render();
	};
}

