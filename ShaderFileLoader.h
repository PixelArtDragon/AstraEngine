#pragma once
#include <string>
#include <glew/glew.h>

namespace Rendering {
	GLuint LoadShaderFile(std::string vertex_shader_file, std::string fragment_shader_file);
}