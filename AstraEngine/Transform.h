#pragma once
#include <glm\mat4x4.hpp>
#include <glm\vec4.hpp>
#include <glm\vec2.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <unordered_set>

class Transform
{
public:
	Transform();
	~Transform();
	//direction vectors
	void rotate(const float angle, glm::vec3 axis);
	void translate(const glm::vec2 translation); //preserves Z-coordinate
	void translate(const glm::vec3 translation); //overrides Z-coordinate
	void translate(const glm::vec4 translation); //for homogeneous coordinates
	//Raw access
	glm::mat4 matrix();
	glm::mat4 localMatrix();

	void SetParent(Transform* parent);

	Transform* parent;

	std::unordered_set<Transform*> children;

	glm::vec3 position() const;
	glm::vec3 scale() const;
	glm::quat rotation() const;

	glm::vec3 localPosition();
	void localPosition(glm::vec3 my_Position);

	glm::vec3 localScale();
	void localScale(glm::vec3 my_Scale);

	glm::quat localRotation();
	void localRotation(glm::quat myRotation);

private:
	glm::vec3 p_localPosition = glm::vec3(0, 0, 0);
	glm::vec3 p_localScale = glm::vec3(1, 1, 1);
	glm::quat p_localRotation;
	glm::mat4 p_cached_localMatrix;
	bool p_recalcMatrix = true;
	std::vector<Transform*> getParentChain();
	std::unordered_set<Transform*> getParentSet();
};
