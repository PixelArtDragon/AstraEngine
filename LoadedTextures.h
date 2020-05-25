#pragma once
#include "Texture.h"
#include <unordered_map>

namespace Rendering {
	std::unordered_map<std::string, Texture> loadedTextures;
}