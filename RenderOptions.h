#pragma once
#include <GL/glew.h>
#include "Rect.h"
#include <glm/vec4.hpp>

class RenderOptions
{
public:
	RenderOptions();
	~RenderOptions();
	
	
	Rect window_bounds;
	
	GLenum cull_face;
	bool culling_enabled;
	glm::vec4 clear_color;
	bool depth_enabled;
	GLfloat clear_depth;
	bool stencil_enabled;
	GLenum depth_function;
	GLenum clear_bits;
	GLenum polygon_mode_face;
	GLenum polygon_mode;

	void Apply(bool shouldClear = true);
};

