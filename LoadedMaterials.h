#pragma once
#include "Material.h"
#include <unordered_map>
#include <string>

namespace Rendering {
	extern std::unordered_map<std::string, Material*> loadedMaterials;
}