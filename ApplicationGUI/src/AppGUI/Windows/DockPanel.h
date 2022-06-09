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

		DockPanel(Graphics& graphics) {
			graphics.CreateSolidColorBrush(D2D1::ColorF(1.0f, 0.5f, 0.0f, 1.0f), &panelBrush);
			transform.setPosition(40, 40);
			transform.setSize(50, 50);
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
		
		void OnDraw(Graphics& graphics) {
			static auto renderTarget = graphics.GetRenderTarget();

			static auto test = transform.positionRectF();

			renderTarget->DrawRoundedRectangle(D2D1::RoundedRect(transform.positionRectF(), 5.0f, 5.0f), panelBrush, 2.0f);
		}
	};
}
