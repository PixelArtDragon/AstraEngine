#pragma once
#include "Transform.h"

namespace Rendering {
	class Camera
	{
	public:
		Camera();
		~Camera();
		virtual Transform* GetTransform();
		virtual glm::mat4 GetView();
		virtual glm::mat4 GetProjection();
		virtual void Update();

		virtual float GetRealDepth(float buffer_depth);
	};
}