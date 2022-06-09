#include "Vector2D.h"

namespace AppGUI {
	
#pragma region Constructors

	Vector2D::Vector2D()
	{
		m_x = 0;
		m_y = 0;
	}

	Vector2D::Vector2D(int x, int y)
	{
		this->m_x = x;
		this->m_y = y;
	}

	Vector2D::Vector2D(const Vector2D& other)
	{
		this->m_x = other.m_x;
		this->m_y = other.m_y;
	}
	
#pragma endregion

#pragma region Getter, Setters

	int Vector2D::getX() const { return m_x; }
	int Vector2D::getY() const { return m_y; }

	int Vector2D::x() const { return m_x; }
	int Vector2D::y() const { return m_y; }

	void Vector2D::setX(int _x) { m_x = _x; }
	void Vector2D::setY(int _y) { m_y = _y; }

	void Vector2D::setXY(int x, int y)
	{
		this->m_x = x;
		this->m_y = y;
	}

	void Vector2D::setXY(const Vector2D other)
	{
		this->m_x = other.m_x;
		this->m_y = other.m_y;
	}

#pragma endregion

#pragma region Methods

	Vector2D Vector2D::normalize() {
		Vector2D result;
		float length = sqrt(m_x * m_x + m_y * m_y);
		return Vector2D(m_x / length, m_y / length);
	}

#pragma endregion

#pragma region Addition operators


	Vector2D Vector2D::operator+(const Vector2D& other) const
	{
		return Vector2D(m_x + other.m_x, m_y + other.m_y);
	}

	Vector2D Vector2D::operator-(const Vector2D& other) const
	{
		return Vector2D(m_x - other.m_x, m_y - other.m_y);
	}

	Vector2D Vector2D::operator+(Vector2D& other)
	{
		return Vector2D(m_x + other.m_x, m_y + other.m_y);
	}

	Vector2D Vector2D::operator-(Vector2D& other)
	{
		return Vector2D(m_x - other.m_x, m_y - other.m_y);
	}

	Vector2D Vector2D::operator*(int n) {
		return Vector2D(m_x * n, m_y * n);
	}

	Vector2D Vector2D::operator/(int n) {
		return Vector2D(m_x / n, m_y / n);
	}
	
#pragma endregion
	
#pragma region Size2D

	int Size2D::getWidth() const { return m_x; }
	int Size2D::getHeight() const { return m_y; }

	int Size2D::width() const { return m_x; }
	int Size2D::height() const { return m_y; }
	
	void Size2D::setWidth(int width) { m_x = width; }
	void Size2D::setHeight(int height) { m_y = height; }
	void Size2D::setSize(int width, int height) { m_x = width; m_y = height; }

	void Size2D::setSize(const Size2D size)
	{
		m_x = size.m_x;
		m_y = size.m_y;
	}
	
#pragma endregion

}
