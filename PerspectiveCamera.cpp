#include "PerspectiveCamera.h"
#include <glm/common.hpp>
#include "Window.h"

namespace Rendering {
	PerspectiveCamera::PerspectiveCamera()
	{
		_transform = new Transform();
		_FOV = 45;
		_z_near = 0.1;
		_z_far = 10;
		recalc_projection = true;
		recalc_view = true;
	}
	PerspectiveCamera::~PerspectiveCamera()
	{
		delete _transform;
	}
	glm::mat4 PerspectiveCamera::GetView()
	{
		if (recalc_view) {
			cached_view = glm::inverse(_transform->matrix());
			//recalc_view = false;
		}
		return cached_view;
	}
	glm::mat4 PerspectiveCamera::GetProjection()
	{
		if (recalc_projection) {
			glm::vec2 calc_window_bounds = window_size();
			cached_projection = glm::perspective(_FOV, calc_window_bounds.x / calc_window_bounds.y, _z_near, _z_far);
			recalc_projection = false;
		}
		return cached_projection;
	}

	Transform * PerspectiveCamera::GetTransform()
	{
		return _transform;
	}

	glm::vec2 PerspectiveCamera::window_size()
	{
		return Window::GetWindowSize();
	}

	float PerspectiveCamera::FOV()
	{
		return _FOV;
	}

	void PerspectiveCamera::FOV(float value)
	{
		_FOV = value;
		recalc_projection = true;
	}

	float PerspectiveCamera::z_near()
	{
		return _z_near;
	}

	float PerspectiveCamera::z_far()
	{
		return _z_far;
	}

	void PerspectiveCamera::z_near(float value)
	{
		_z_near = value;
		recalc_projection = true;
	}

	void PerspectiveCamera::z_far(float value)
	{
		_z_far = value;
		recalc_projection = true;
	}
	float PerspectiveCamera::GetRealDepth(float buffer_depth)
	{
		return -(_z_far * _z_near) / (buffer_depth * (_z_far * _z_near) - _z_far);
	}
}