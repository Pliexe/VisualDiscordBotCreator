/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE
 */
#include "BaseWindow.h"

namespace AppGUI {
	inline LRESULT BaseWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		BaseWindow* pThis = NULL;

		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (BaseWindow*)pCreate->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->m_hWnd = hWnd;
		}
		else {
			pThis = (BaseWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		}

		if (pThis)
		{
			//switch (uMsg)
			//{
			//	/*case WM_DESTROY:
			//		PostQuitMessage(0);
			//		break;*/
			//default:
			//	return pThis->HandleProc(uMsg, wParam, lParam);
			//}

			return pThis->HandleProc(uMsg, wParam, lParam);
			
		}
		else return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	
}