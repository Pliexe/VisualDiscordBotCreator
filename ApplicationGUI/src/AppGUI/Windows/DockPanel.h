#pragma once

#include "AppGUI/Graphics/Transform.h"
#include "AppGUI/Graphics/Graphics.h"

namespace AppGUI {
	class DockPanel
	{
	private:

		Transform transform;
		
		typedef struct DockedPanels {
			DockPanel *top = nullptr;
			DockPanel *bottom = nullptr;
			DockPanel *left = nullptr;
			DockPanel *right = nullptr;
		} DockedPanels;

		DockedPanels dockedPanels;
		
		ID2D1SolidColorBrush* panelBrush;

	public:

		DockPanel(Graphics& graphics, int x, int y, int w, int h) {
			graphics.CreateSolidColorBrush(D2D1::ColorF(1.0f, 0.5f, 0.0f, 1.0f), &panelBrush);
			transform.setPosition(x, y);
			transform.setSize(w, h);
		}

		~DockPanel() {
			panelBrush->Release();
		}
		
		bool OnHover(int x, int y) {
			if (transform.isPointInside(x, y)) {



				
				return true;
			}
			else return false;
		}
		
		void OnDraw(ID2D1HwndRenderTarget *renderTarget) {

			static auto test = transform.positionRectF();

			renderTarget->DrawRoundedRectangle(D2D1::RoundedRect(transform.positionRectF(), 5.0f, 5.0f), panelBrush, 2.0f);
		}
	};
}
