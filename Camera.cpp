#include "Camera.h"

namespace Rendering {

	Camera::Camera()
	{
	}


	Camera::~Camera()
	{
	}

	Transform * Rendering::Camera::GetTransform()
	{
		return nullptr;
	}

	glm::mat4 Rendering::Camera::GetView()
	{
		return glm::mat4();
	}

	glm::mat4 Rendering::Camera::GetProjection()
	{
		return glm::mat4();
	}
	void Camera::Update()
	{
	}
}