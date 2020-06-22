#pragma once
#include <GL/glew.h>
class FrameBuffer
{
public:
	FrameBuffer(size_t width, size_t height);
	FrameBuffer(size_t width, size_t height, bool use_texture, bool use_depth);
	~FrameBuffer();
	GLuint fbo;
	GLuint texture;
	GLuint depth_buffer;
};

