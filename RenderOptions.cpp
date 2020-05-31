#include "RenderOptions.h"



RenderOptions::RenderOptions()
{
	polygon_mode_face = GL_FRONT;
	polygon_mode = GL_FILL;
}


RenderOptions::~RenderOptions()
{
}

void RenderOptions::Apply()
{
	glViewport(window_bounds.x, window_bounds.y, window_bounds.width, window_bounds.height);
	if (depth_enabled) {
		glEnable(GL_DEPTH_TEST);
	} else {
		glDisable(GL_DEPTH_TEST);
	}
	glClearDepth(clear_depth);
	glDepthFunc(depth_function);
	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
	glClear(clear_bits);
	if (culling_enabled) {
		glEnable(GL_CULL_FACE);
		glCullFace(cull_face);
	} else {
		glDisable(GL_CULL_FACE);
	}
	glPolygonMode(polygon_mode_face, polygon_mode);
}
