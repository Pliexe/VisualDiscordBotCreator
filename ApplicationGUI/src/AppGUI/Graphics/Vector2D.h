#pragma once

#include "pch.h"
#include "AppGUI/Core.h"

namespace AppGUI {

	class GUI_API Vector2D
	{
	protected:
		int m_x, m_y;

	public:
		Vector2D();
		Vector2D(int x, int y);
		Vector2D(const Vector2D&);

		inline int getX() const;
		inline int getY() const;

		inline int x() const;
		inline int y() const;

		void setX(int x);
		void setY(int y);

		void setXY(int x, int y);
		void setXY(const Vector2D);

		Vector2D normalize();

		Vector2D operator+(const Vector2D& v) const;
		Vector2D operator-(const Vector2D& v) const;		
		Vector2D operator+(Vector2D& v);
		Vector2D operator-(Vector2D& v);
		Vector2D operator*(int n);
		Vector2D operator/(int n);
	};

	class GUI_API Size2D : Vector2D
	{
	public:
		Size2D(int width, int height) : Vector2D(width, height) { }
		Size2D() : Vector2D() {}
		Size2D(const Size2D& size) : Vector2D(size) { }
		Size2D(const Vector2D& size) : Vector2D(size) { }

		Vector2D normalize() = delete;

		inline int getWidth() const;
		inline int getHeight() const;

		inline int width() const;
		inline int height() const;
		
		void setWidth(int width);
		void setHeight(int height);
		void setSize(int width, int height);
		void setSize(const Size2D size);
	};
}

