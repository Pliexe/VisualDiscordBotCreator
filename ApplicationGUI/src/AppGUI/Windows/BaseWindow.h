/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE
 */
#pragma once

#include "AppGUI/Core.h"
#include "pch.h"

namespace AppGUI {
	class GUI_API BaseWindow
	{
	private:
		//bool Create(wchar_t windowName, );

	protected:

		HWND hWndParent = NULL;
		
		LRESULT virtual HandleProc(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
		static LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		BaseWindow(HWND _hWndParent) : hWndParent(_hWndParent) {}
		//virtual ~BaseWindow() = 0;

		HWND m_hWnd;

		bool virtual Create(int x, int y, int width, int height) = 0;
		bool virtual Show(int nCmdShow) = 0;

		PCWSTR ClassName = L"2D DX Window";
	};
	
}