#include "Transform.h"

namespace AppGUI {

#pragma region Constructors

	Transform::Transform()
	{
		m_parent = nullptr;
		m_position = new Vector2D();
		m_size = new Size2D();
	}

	Transform::Transform(Vector2D position, Size2D size, Transform* parent)
	{
		m_position = new Vector2D(position);
		m_size = new Size2D(size);
		m_parent = parent;
	}

	Transform::Transform(Vector2D* position, Size2D* size, Transform* parent)
	{
		m_position = new Vector2D(*position);
		m_size = new Size2D(*size);
		m_parent = parent;
	}

	Transform::Transform(int x, int y, int width, int height, Transform* parent)
	{
		m_position = new Vector2D(x, y);
		m_size = new Size2D(width, height);
		m_parent = parent;
	}

	Transform::~Transform()
	{
		delete m_position;
		delete m_size;
	}
	
#pragma endregion

#pragma region Getters and Setters

	Vector2D& Transform::getPosition() const { return *m_position; }
	Size2D& Transform::getSize() const { return *m_size; }
	Vector2D& Transform::position() { return *m_position; }
	Size2D& Transform::size() { return *m_size; }
	
	Transform& Transform::getParent() const { return *m_parent; }
	Transform& Transform::parent() { return *m_parent; }
	Transform* Transform::getParentPtr() const { return m_parent; }
	bool Transform::hasParent() const { return m_parent != nullptr; }
	
	void Transform::setPosition(Vector2D position) { m_position->setXY(position); }
	void Transform::setSize(Size2D size) { m_size->setSize(size); }
	void Transform::setPosition(float x, float y) { m_position->setXY(x, y); }
	void Transform::setSize(float width, float height) { m_size->setSize(width, height); }
	void Transform::setParent(Transform* parent) { m_parent = parent; }

#pragma endregion

#pragma region Methods

	bool Transform::isPointInside(Vector2D position) {
		return (position.x() >= m_position->x() && position.x() <= m_position->x() + m_size->width() &&
			position.y() >= m_position->y() && position.y() <= m_position->y() + m_size->height());
	}

	bool Transform::isPointInside(float x, float y) {
		return (x >= m_position->x() && x <= m_position->x() + m_size->width() &&
			y >= m_position->y() && y <= m_position->y() + m_size->height());
	}

#pragma endregion

}