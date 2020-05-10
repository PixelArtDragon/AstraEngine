#pragma once
#include <glm/vec2.hpp>
#include "Shader.h"
#include "Drawable3D.h"
#include "Camera.h"

namespace Rendering {
	void Init();
	void Reshape(glm::vec2 newDimensions);

	void RenderFrame();
	
	void AddDrawable(Drawable3D* drawable);

	Camera & GetActiveCamera();
	extern Camera * camera;
}