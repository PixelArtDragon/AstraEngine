#include "Rect.h"



Rect::Rect(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Rect Rect::fromMidpoint(glm::vec2 midpoint, glm::vec2 size)
{
	return Rect(midpoint.x - size.x/2, midpoint.y - size.y/ 2, size.x, size.y);
}

Rect::Rect()
{
}


Rect::~Rect()
{
}

float Rect::top() const
{
	return y + height;
}
float Rect::bottom() const
{
	return y;
}

float Rect::right() const
{
	return x + width;
}
float Rect::left() const
{
	return x;
}

glm::vec2 Rect::midpoint() const
{
	return glm::vec2(x + (width / 2), y + (height / 2));
}

glm::vec2 Rect::size() const
{
	return glm::vec2(width, height);
}

//Vector2 Rect::bottomLeft()
//{
//	return Vector2(x, y);
//}
//
//Vector2 Rect::bottomRight()
//{
//	return Vector2(right(), y);
//}
//
//Vector2 Rect::topLeft()
//{
//	return Vector2(top(), y);
//}
//
//Vector2 Rect::topRight()
//{
//	return Vector2(top(), right());
//}

glm::vec2 Rect::bottomLeft() const
{
	return glm::vec2(x, y);
}

glm::vec2 Rect::bottomRight() const
{
	return glm::vec2(right(), y);
}

glm::vec2 Rect::topLeft() const
{
	return glm::vec2(x, top());
}

glm::vec2 Rect::topRight() const
{
	return glm::vec2(right(), top());
}

bool Rect::overlaps(const Rect & other)
{
	if (abs(this->midpoint().x - other.midpoint().x) > (this->width + other.width) / 2.0f) return false;
	if (abs(this->midpoint().y - other.midpoint().y) > (this->height + other.height) / 2.0f) return false;
	return true;
}

Rect Rect::inverse() const
{
	return Rect(x + width, y + height, -width, -height);
}


