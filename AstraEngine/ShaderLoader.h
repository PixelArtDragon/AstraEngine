#pragma once
#include <string>
#include "Shader.h"

namespace Rendering {
	enum ShaderType {
		Vertex,
		Fragment
	};
	Shader* LoadShaderFromFile(const std::string & filename, ShaderType shaderType);
}