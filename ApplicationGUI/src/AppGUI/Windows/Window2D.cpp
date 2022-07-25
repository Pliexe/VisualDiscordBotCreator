/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE
 */
#include "Window2D.h"

bool IsMaximized(HWND hWnd) {

	WINDOWPLACEMENT wp = { sizeof(WINDOWPLACEMENT) };
	GetWindowPlacement(hWnd, &wp);

	return wp.showCmd == SW_MAXIMIZE;
}

inline bool IsWindows11OrGreater()
{
	// Checking if build number is higher than 22000 since that's where Windows 11 was released
	OSVERSIONINFOEXW osinfo = { sizeof(osinfo), HIBYTE(_WIN32_WINNT_WIN10), LOBYTE(_WIN32_WINNT_WIN10), 22000, 0, { 0 }, 0, 0 };

	DWORDLONG const vermask = VerSetConditionMask(
		VerSetConditionMask(
			VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL),
			VER_MINORVERSION, VER_GREATER_EQUAL),
		VER_BUILDNUMBER, VER_GREATER_EQUAL
	);

	return VerifyVersionInfoW(&osinfo, VER_MAJORVERSION | VER_MINORVERSION | VER_BUILDNUMBER, vermask);
}

namespace AppGUI {
	Window2D::Window2D(HWND _hWndParent, bool _isMain) : BaseWindow(_hWndParent), isMain(_isMain) {
		graphics = new Graphics();
	}

	Window2D::~Window2D() {
		Application::getInstance()->UnregisterWindow(this);
		if (graphics->GetRenderTarget() != NULL) {
			titleBarBrush->Release();
			titleBarIconBrush->Release();
			delete graphics;
		}
	}
	
	bool Window2D::Create(int x, int y, int width, int height)
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
			wc.style = CS_DROPSHADOW;

			RegisterClass(&wc);
		}

		m_hWnd = CreateWindowEx(
			NULL,
			ClassName, isMain ? L"Main Window 2D" : L"Window 2D", 
			WS_OVERLAPPEDWINDOW,
			x, y, width, height,
			hWndParent, NULL, GetModuleHandle(NULL), this
		);

		if (m_hWnd == NULL) return false;

		
		// Check if on Windows 11
		if (IsWindows11OrGreater()) {
			// Windows 11 Styling
			//MessageBox(NULL, L"Using Windows 11", L"WINVERSION", MB_OK);
			DWM_WINDOW_CORNER_PREFERENCE prefrence = DWMWCP_ROUND;
			DwmSetWindowAttribute(m_hWnd, DWMWA_WINDOW_CORNER_PREFERENCE, &prefrence, sizeof(prefrence));
		}

		//SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_CAPTION);

		return true;
	}

	bool Window2D::Init() {
		if (!graphics->Init(m_hWnd)) {
			delete graphics;
			return false;
		}
		auto target = graphics->GetRenderTarget();

		target->CreateSolidColorBrush(D2D1::ColorF(0.34f, 0.32f, 0.32f, 1), &titleBarBrush);
		target->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1, 1), &titleBarIconBrush);

		graphics->GetWriteFactory()->CreateTextFormat(L"Plantagenet Cherokee", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 15, L"", &textFormat);
		textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		dockedPanels.push_back(new DockPanel(*graphics));

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

		auto renderTarget = graphics->GetRenderTarget();

		ID2D1SolidColorBrush* tempBrush;
		graphics->CreateSolidColorBrush(D2D1::ColorF(1.0f, 0.5f, 0.5f, 1.0f), &tempBrush);

		for (std::vector<DockPanel*>::iterator it = dockedPanels.begin(), end = dockedPanels.end(); it != end; ++it)
		{
			std::cout << "Rendering " << (isMain ? "main" : "side") << "Window" << std::endl;
			(*it)->OnDraw(*graphics, tempBrush);
			
			renderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(150.0f, 150.0f), 5.0f, 5.0f), tempBrush, 2.0f);
		}

		tempBrush->Release();

		// Render Title bar
		RenderTitleBar();

		graphics->EndDraw();
	}

	void Window2D::RenderTitleBar()
	{
		auto renderTarget = graphics->GetRenderTarget();
		
		renderTarget->FillRectangle(D2D1::RectF(0, 0, m_width, 25), titleBarBrush);
		
		// X
		renderTarget->DrawLine(D2D1::Point2F(m_width - 25, 20), D2D1::Point2F(m_width - 10, 5), titleBarIconBrush, 1.5f);
		renderTarget->DrawLine(D2D1::Point2F(m_width - 10, 20), D2D1::Point2F(m_width - 25, 5), titleBarIconBrush, 1.5f);
		// O
		
		if (IsMaximized(m_hWnd)) {
			renderTarget->DrawRectangle(D2D1::RectF(m_width - 52, 5, m_width - 40, 17), titleBarIconBrush, 1.5f);
			renderTarget->FillRectangle(D2D1::RectF(m_width - 55, 8, m_width - 43, 20), titleBarBrush);
			renderTarget->DrawRectangle(D2D1::RectF(m_width - 55, 8, m_width - 43, 20), titleBarIconBrush, 1.5f);
		} else renderTarget->DrawRectangle(D2D1::RectF(m_width - 55, 5, m_width - 40, 20), titleBarIconBrush, 1.5f);
		// -
		renderTarget->DrawLine(D2D1::Point2F(m_width - 70, 13), D2D1::Point2F(m_width - 85, 13), titleBarIconBrush, 1.5f);

		auto str = std::to_wstring(titleBarBrush->GetColor().r) + 
			L" " + std::to_wstring(titleBarBrush->GetColor().g) +
			L" " + std::to_wstring(titleBarBrush->GetColor().b) +
			L" " + std::to_wstring(titleBarBrush->GetColor().a);

		renderTarget->DrawText(str.c_str(), str.length(), textFormat, D2D1::RectF(15, 100, m_width, 20), titleBarIconBrush);
	}

	LRESULT Window2D::HandleProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		static bool close_highlighted = false;

		switch (uMsg)
		{
		case WM_SIZE:
		case WM_SIZING:
			if (graphics) {
				RECT client_rect;
				GetClientRect(m_hWnd, &client_rect);
				// Update stored props to new heights
				m_width = client_rect.right;
				m_height = client_rect.bottom;
				graphics->Resize(client_rect.right, client_rect.bottom); // Resize "screen size" of D2 render target
				Render(); // Render smooth updates
#ifdef _DEBUG
				std::cout << "Resizing window | Width: " << m_width << ", Height: " << m_height << std::endl;
#endif // _DEBUG

			}
			return 0;
		case WM_CLOSE:
			if (isMain && MessageBox(m_hWnd, L"Are you sure you want to exit?", L"Exit", MB_YESNO) != IDYES) return 0;
			DestroyWindow(m_hWnd);
			return 0;
		case WM_NCMOUSEMOVE:
		{

		}
		case WM_NCLBUTTONDOWN:
		{
			switch (wParam) {
			case HTMAXBUTTON:
			case HTMINBUTTON:
			case HTCLOSE:
				return 0;
			default:
				return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
			}
			break;
		}
		case WM_NCLBUTTONUP:
		{
			switch (wParam) {
			case HTCLOSE:
				PostMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
				return 0;
			case HTMINBUTTON:
				PostMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
				return 0;
			case HTMAXBUTTON:
				if (IsMaximized(m_hWnd))
					PostMessage(m_hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
				else
					PostMessage(m_hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
				return 0;
			default:
				return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
			}
			break;
		}
		case WM_NCCALCSIZE:
		{
			if (IsMaximized(m_hWnd)) {
				InflateRect((LPRECT)lParam, -8, -8); // Decrease client area to fit maximized state
			}
			break;
		}
		case WM_NCHITTEST:
		
		{
			RECT rc;
			POINT pt;

			GetCursorPos(&pt);

			GetWindowRect(m_hWnd, &rc);

			const int border_width = 5;

			if (pt.x <= rc.right && pt.x >= rc.left && pt.y <= rc.bottom && pt.y >= rc.top)
			{
				POINT relative = { pt.x - rc.left, pt.y - rc.top };

				std::cout << "Real Relative > X: " << relative.x << ", Y: " << relative.y;

				if (IsMaximized(m_hWnd)) {
					relative.x -= 8;
					relative.y -= 8;
				}

				std::cout << " | Modified Relative > X: " << relative.x << ", Y: " << relative.y << " | x: " << m_width - relative.x << std::endl;

				if (relative.y <= 25) {
					//MessageBox(m_hWnd, std::wstring(L"Yes or no: " + std::wstring(((relative.x <= m_width - 25 && relative.x >= m_width - 10) ? L"true" : L"false")) + L", Cords: " + std::to_wstring(m_width - relative.x) + L" " + std::to_wstring(relative.y) + L", BRUH: " + std::to_wstring(relative.x) + L" <= " + std::to_wstring(m_width - 25) + L" && " + std::to_wstring(relative.x) + L" >= " + std::to_wstring(m_width - 10)).c_str(), L"Cords", MB_OK);
					if (m_width - relative.x <= 25 && m_width - relative.x >= 10 && relative.y <= 20 && relative.y >= 5)
						return HTCLOSE;
					else if (m_width - relative.x <= 55 && m_width - relative.x >= 40 && relative.y <= 20 && relative.y >= 5)
						return HTMAXBUTTON;
					else if (m_width - relative.x <= 85 && m_width - relative.x >= 70 && relative.y <= 20 && relative.y >= 5)
						return HTMINBUTTON;
					else if (relative.y <= border_width)
					{
						if (relative.x <= border_width)
							return HTTOPLEFT;
						else if (relative.x >= m_width - border_width)
							return HTTOPRIGHT;
						else return HTTOP;
					}
					else return HTCAPTION;
				}
				else {

					if (relative.y >= m_height - border_width)
					{
						if (relative.x <= border_width)
							return HTBOTTOMLEFT;
						else if (relative.x >= m_width - border_width)
							return HTBOTTOMRIGHT;
						else return HTBOTTOM;
					}
					else {
						if (relative.x <= border_width)
							return HTLEFT;
						else if (relative.x >= m_width - border_width)
							return HTRIGHT;
					}


					//return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
					return DefWindowProc(m_hWnd, uMsg, wParam, lParam);

				}

			}



			break;
		}



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