/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE
 */
#pragma once

#include "pch.h"

namespace AppGUI {
	class Graphics
	{
	private:
		ID2D1Factory* factory;
		ID2D1HwndRenderTarget* renderTarget;
		IDWriteFactory* writeFactory;

		ID2D1SolidColorBrush* brush;
	public:
		Graphics();
		~Graphics();
		
		inline ID2D1HwndRenderTarget* GetRenderTarget() const { return renderTarget; }
		inline IDWriteFactory* GetWriteFactory() const { return writeFactory; }
		
		bool Init(HWND hWnd);

		void ClearScreen(int r, int g, int b) { renderTarget->Clear(D2D1::ColorF(r, g, b)); }
		void BeginDraw() { renderTarget->BeginDraw(); }
		void EndDraw() { renderTarget->EndDraw(); }

		void Resize(int width, int height);
	};
}