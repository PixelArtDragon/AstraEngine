#pragma once
#include <glew/glew.h>
#include "Drawable3D.h"

namespace Rendering {
	class ShadowBuffer
	{
	public:
		ShadowBuffer(size_t size);
		~ShadowBuffer();
		GLuint fbo;
		GLuint depth_texture;
	};
}