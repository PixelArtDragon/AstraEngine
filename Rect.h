#pragma once
#include <glm\vec2.hpp>

struct Rect
{
public:
	Rect(float x, float y, float width, float height);
	static Rect fromMidpoint(glm::vec2 midpoint, glm::vec2 size);
	Rect();
	~Rect();
	float x;
	float y;
	float width;
	float height;
	float top() const;
	float bottom() const;
	float right() const;
	float left() const;
	glm::vec2 midpoint() const;
	glm::vec2 size() const;
	glm::vec2 bottomLeft() const;
	glm::vec2 bottomRight() const;
	glm::vec2 topLeft() const;
	glm::vec2 topRight() const;
	bool overlaps(const Rect & other);
	Rect inverse() const;
};

