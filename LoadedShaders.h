#pragma once
#include "Shader.h"
#include <string>
#include <unordered_map>

namespace Rendering {
	extern std::unordered_map<std::string, Shader*> loadedShaders;
}