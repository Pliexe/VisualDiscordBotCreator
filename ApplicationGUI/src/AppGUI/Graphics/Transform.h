#pragma once

#include "pch.h"
#include "Vector2D.h"
#include "AppGUI/Core.h"

namespace AppGUI {
	class GUI_API Transform
	{
	protected:
		Vector2D* m_position;
		Size2D* m_size;

		Transform* m_parent;
	public:
		Transform();
		Transform(Vector2D position, Size2D size = Size2D(50, 50), Transform* parent = nullptr);
		Transform(Vector2D* position, Size2D* size = new Size2D(50, 50), Transform* parent = nullptr);
		Transform(int x, int y, int width = 50, int height = 50, Transform* parent = nullptr);

		~Transform();
		
		Vector2D& getPosition() const;
		//Vector2D getLocalPosition() const;
		Size2D& getSize() const;

		Vector2D& position();
		//Vector2D localPosition() const;
		Size2D& size();

		D2D1_RECT_U positionRectU() {
			return D2D1::RectU(m_position->x(), m_position->y(), m_position->x() + m_size->width(), m_position->y() + m_size->height());
		}

		D2D1_RECT_F positionRectF() {
			return D2D1::RectF(m_position->x(), m_position->y(), m_position->x() + m_size->width(), m_position->y() + m_size->height());
		}

		bool isPointInside(Vector2D point);
		bool isPointInside(float x, float y);

		bool hasParent() const;

		void setPosition(Vector2D position);
		void setPosition(float x, float y);
		//void setLocalPosition(Vector2D position);
		//void setLocalPosition(float x, float y);
		
		void setSize(Size2D size);
		void setSize(float width, float height);

		void setParent(Transform* parent);
		Transform& getParent() const;
		Transform& parent();
		Transform* getParentPtr() const;
	};
}