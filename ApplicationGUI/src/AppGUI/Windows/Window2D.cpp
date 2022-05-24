/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE
 */
#include "Window2D.h"

namespace AppGUI {
	Window2D::Window2D(HWND _hWndParent, bool _isMain) : BaseWindow(_hWndParent), isMain(_isMain) {
		graphics = new Graphics();
	}

	Window2D::~Window2D() {
		Application::getInstance()->UnregisterWindow(this);
		delete graphics;
	}
	
	bool Window2D::Create(int x, int y, int width, int height, DWORD dwStyle, DWORD dwExStyle)
	{
		m_width = width;
		m_height = height;
		
		WNDCLASS wc;
		ZeroMemory(&wc, sizeof(WNDCLASS));

		if (!GetClassInfo(GetModuleHandle(NULL), ClassName, &wc)) {
			wc.lpfnWndProc = Window2D::WindowProc;
			wc.hInstance = GetModuleHandle(NULL);
			wc.lpszClassName = ClassName;
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);

			RegisterClass(&wc);
		}

		m_hWnd = CreateWindowEx(
			dwExStyle, ClassName, isMain ? L"Main Window 2D" : L"Window 2D", dwStyle, x, y,
			width, height, hWndParent, NULL, GetModuleHandle(NULL), this
		);

		return m_hWnd ? true : false;
	}

	bool Window2D::Init() {
		if (!graphics->Init(m_hWnd)) {
			delete graphics;
			return false;
		}
		return true;
	}

	void Window2D::Update()
	{
		
	}

	void Window2D::Render()
	{
		if (graphics->GetRenderTarget() == NULL) return;
		graphics->BeginDraw();

		graphics->ClearScreen(0.0f, 0.0f, 0.0f);

		ID2D1SolidColorBrush* brush;
		graphics->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(25.0f, 25.0f, 25.0f, 1.0f), &brush);

		graphics->GetRenderTarget()->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(rand() % 400, 50), 50, 50), brush, 3.0f);

		graphics->EndDraw();
	}

	LRESULT Window2D::HandleProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT move = NULL;

		switch (uMsg)
		{
		/*case WM_GETMINMAXINFO:
		{
			RECT WorkArea; SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);

			((MINMAXINFO*)lParam)->ptMaxSize.x = (WorkArea.right - WorkArea.left);
			((MINMAXINFO*)lParam)->ptMaxSize.y = (WorkArea.bottom - WorkArea.top);
			((MINMAXINFO*)lParam)->ptMaxPosition.x = WorkArea.left;
			((MINMAXINFO*)lParam)->ptMaxPosition.y = WorkArea.top;

			return 0;
		}*/
		case WM_CLOSE:
			if (isMain) {
				if (MessageBox(m_hWnd, L"Are you sure you want to exit?", L"Exit", MB_YESNO) == IDYES)
					DestroyWindow(m_hWnd);
			} else DestroyWindow(m_hWnd);
			return 0;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(m_hWnd, &ps);

			RECT rect;
			HBRUSH brush;
			
			GetClientRect(m_hWnd, &rect);
			rect.bottom = 40;
			
			brush = CreateSolidBrush(RGB(40, 44, 52));
			
			FillRect(hdc, &rect, brush);

			
			
			EndPaint(m_hWnd, &ps);
			break;
		}
		case WM_NCHITTEST:
			RECT rc;
			POINT pt;

			GetCursorPos(&pt);

			GetWindowRect(m_hWnd, &rc);
			rc.bottom = rc.bottom - m_height + 40;

			//if cursor position is within top layered drawn rectangle then  
			//set move to HTCAPTION for moving the window from its client  
			if (pt.x <= rc.right && pt.x >= rc.left && pt.y <= rc.bottom && pt.y >= rc.top)
			{
				move = DefWindowProc(m_hWnd, uMsg, wParam, lParam);
				if (move == HTCLIENT)
				{
					move = HTCAPTION;
				}
			}

			return move;

			break;

		case WM_DESTROY:
			if (isMain) {
				PostQuitMessage(0);
			}
			return 0;
		case WM_NCDESTROY:
			delete this;
			break;
		default:
			return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
		}
		return 0;
	}
}