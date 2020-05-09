#pragma once
#include "Camera.h"

namespace Rendering {
	class DefaultCamera : public Camera
	{
	public:
		DefaultCamera();
		~DefaultCamera();
		Transform * GetTransform() override;
	private:
		Transform * transform;
	};

}