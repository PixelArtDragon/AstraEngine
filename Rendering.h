#pragma once
#include <glm/vec2.hpp>
#include "Shader.h"
#include "Drawable3D.h"
#include "Camera.h"
#include "LightSource.h"

namespace Rendering {
	void Init();
	void Reshape(glm::vec2 newDimensions);

	void RenderFrame();

	extern Lightsource* light_source;
	
	void AddDrawable(Drawable3D* drawable);
	void RemoveDrawable(Drawable3D* drawable);

	Camera & GetActiveCamera();
	extern Camera * camera;
}