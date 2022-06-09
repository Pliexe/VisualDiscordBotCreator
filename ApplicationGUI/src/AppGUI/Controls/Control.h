/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE
 */
#pragma once

#include "pch.h"
#include "AppGUI/Graphics/Transform.h"

namespace AppGUI {

	//typedef Vector2D 
	
	

	class BaseControl
	{
	public:
		enum Anchor {
			Center = 0,
			Top = 1 << 0,
			Bottom = 1 << 1,
			Left = 1 << 2,
			Right = 1 << 3,
		};

		enum Scale {
			None = 0,
			Horizontal = 1 << 0,
			Vertical = 1 << 1,
			Width = 1 << 2,
			Height = 1 << 3,
			Both = Horizontal | Vertical,
		};

		
	protected:
		
		int m_anchor;
		int m_scale;
		int baseX, baseY, baseWidth, baseHeight;

		Transform transform;
		
		void calculateParentResize();
		void calculateTransform();

	public:
		
		void _onParentResize();
		virtual void onParentResize() { }

		BaseControl() = delete;
		BaseControl(int x, int y, int width, int height, int anchor = Anchor::Top | Anchor::Left, int scale = Scale::None) : baseX(x), baseY(y), baseWidth(width), baseHeight(height), m_anchor(anchor), m_scale(scale), transform(x, y, width, height) { calculateTransform(); }
		BaseControl(int x, int y, int width, int height, Transform &parent, int anchor = Anchor::Top | Anchor::Left, int scale = Scale::None) : baseX(x), baseY(y), baseWidth(width), baseHeight(height), m_anchor(anchor), m_scale(scale), transform(x, y, width, height, &parent) { calculateTransform(); }
		BaseControl(Vector2D position, Vector2D size, int anchor = Anchor::Top | Anchor::Left, int scale = Scale::None) : baseX(position.x()), baseY(position.y()), baseWidth(size.x()), baseHeight(size.y()), m_anchor(anchor), m_scale(scale), transform(position, size) { calculateTransform(); }
		BaseControl(Vector2D position, Vector2D size, Transform& parent, int anchor = Anchor::Top | Anchor::Left, int scale = Scale::None) : baseX(position.x()), baseY(position.y()), baseWidth(size.x()), baseHeight(size.y()), m_anchor(anchor), m_scale(scale), transform(position, size, &parent) { calculateTransform(); }

		void virtual OnDraw() = 0;
		

		
	};

}