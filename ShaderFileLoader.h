#pragma once
#include <glew/glew.h>
#include <string>

namespace Rendering {
	GLuint LoadShaderFile(std::string vertex_shader_file, std::string fragment_shader_file);
}