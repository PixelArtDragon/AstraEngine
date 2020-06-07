#pragma once
#include "Camera.h"
#include "Rect.h"

namespace Rendering {
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera();
		~PerspectiveCamera();

		glm::mat4 GetView() override;
		glm::mat4 GetProjection() override;
		Transform* GetTransform() override;

		glm::vec2 window_size();

		float FOV();
		void FOV(float value);

		float z_near();
		float z_far();
		void z_near(float value);
		void z_far(float value);

		virtual float GetRealDepth(float buffer_depth) override;

	private:
		Transform * _transform;

		float _z_near;
		float _z_far;
		float _FOV;

		bool recalc_projection;
		glm::mat4 cached_projection;
		bool recalc_view;
		glm::mat4 cached_view;
	};
}