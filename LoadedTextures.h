#pragma once
#include "Texture.h"
#include <unordered_map>

namespace Rendering {
	extern std::unordered_map<std::string, Texture> loadedTextures;
}