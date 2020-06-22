#pragma once
#include <GL/glew.h>
#include <string>

namespace Rendering {
	struct Texture
	{
		Texture();
		Texture(std::string image_file);
		GLuint texture_id;
	};
}