#pragma once
#include <glm/vec2.hpp>
#include "Shader.h"
#include "Drawable3D.h"
#include "Renderable.h"
#include "Camera.h"
#include "LightSource.h"
#include "RenderOptions.h"

namespace Rendering {
	void Init();
	void Reshape(glm::vec2 newDimensions);

	void RenderFrame();

	extern Lightsource* light_source;
	
	void AddDrawable(Drawable3D* drawable);
	void RemoveDrawable(Drawable3D* drawable);

	void AddRenderable(Renderable* renderable);
	void RemoveRenderable(Renderable* renderable);

	Camera & GetActiveCamera();
	extern Camera * camera;
	extern RenderOptions rendering_options;

	float getDepth(glm::vec2 screen_point);

	glm::vec3 ScreenPointToWorldPosition(glm::vec2 screen_point);
}