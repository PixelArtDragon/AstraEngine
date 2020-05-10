#include "Transform.h"
#include <glm\vec4.hpp>
#include <glm\gtx\transform.hpp>

Transform::Transform()
{
}


Transform::~Transform()
{

}

void Transform::rotate(const float angle, glm::vec3 axis)
{
	p_localRotation = glm::rotate(p_localRotation, angle, axis);
	p_recalcMatrix = true;
}

void Transform::translate(const glm::vec2 translation)
{
	p_localPosition += glm::vec3(translation, 0.0);
	p_recalcMatrix = true;
}

void Transform::translate(const glm::vec3 translation)
{
	p_localPosition += translation;
	p_recalcMatrix = true;
}

void Transform::translate(const glm::vec4 translation)
{
	p_localPosition += glm::vec3(translation);
	p_recalcMatrix = true;
}


glm::mat4 Transform::matrix()
{
	return (parent == nullptr ? localMatrix() : parent->matrix() * localMatrix());
}

glm::mat4 Transform::localMatrix()
{
	//glm::mat4 myMatrix = glm::mat4(1.0f);
	//myMatrix = glm::scale(myMatrix, localScale);
	//myMatrix = glm::rotate(myMatrix, glm::radians(180.0f), glm::eulerAngles(localRotation));
	//myMatrix = glm::toMat4(localRotation) * myMatrix;
	//myMatrix = glm::translate(myMatrix, localPosition);
	//return myMatrix;
	if (p_recalcMatrix) {
		p_cached_localMatrix = glm::translate(p_localPosition) * glm::toMat4(p_localRotation) * glm::scale(p_localScale);
	}
	p_recalcMatrix = false;
	return p_cached_localMatrix;
}

void Transform::SetParent(Transform* newParent)
{
	std::unordered_set<Transform*> parentSet = newParent->getParentSet();
	if (parentSet.find(this) != parentSet.end()) {
		//If this is already a parent of the new parent, return so that a loop isn't created
		return;
	}
	else {
		if (this->parent != nullptr) {
			this->parent->children.erase(this);
		}
		newParent->children.insert(this);
		this->parent = newParent;
	}
}

glm::vec3 Transform::position() const
{
	if (parent != nullptr) {
		return parent->matrix() * glm::vec4(p_localPosition, 1.0);
	} else {
		return p_localPosition;
	}
}

glm::vec3 Transform::scale() const
{
	if (parent != nullptr) {
		return p_localScale * parent->scale();
	} else {
		return p_localScale;
	}
}

glm::quat Transform::rotation() const
{
	if (parent != nullptr) {
		return parent->rotation() * p_localRotation;
	} else {
		return p_localRotation;
	}
}

glm::vec3 Transform::localPosition()
{
	return p_localPosition;
}

void Transform::localPosition(glm::vec3 my_Position)
{
	p_localPosition = my_Position;
	p_recalcMatrix = true;
}

glm::vec3 Transform::localScale()
{
	return p_localScale;
}

void Transform::localScale(glm::vec3 my_Scale)
{
	p_localScale = my_Scale;
	p_recalcMatrix = true;

}

glm::quat Transform::localRotation()
{
	return p_localRotation;
}

void Transform::localRotation(glm::quat myRotation)
{
	p_localRotation = myRotation;
	p_recalcMatrix = true;
}

std::vector<Transform*> Transform::getParentChain()
{
	if (parent != nullptr) {
		std::vector<Transform*> parentchain = parent->getParentChain();
		parentchain.push_back(this);
		return parentchain;
	}
	else {
		return std::vector<Transform*>();
	}
}std::unordered_set<Transform*> Transform::getParentSet()
{
	if (parent != nullptr) {
		std::unordered_set<Transform*> parentset = parent->getParentSet();
		parentset.insert(this);
		return parentset;
	}
	else {
		return std::unordered_set<Transform*>();
	}
}

