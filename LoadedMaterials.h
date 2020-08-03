#pragma once
#include "Material.h"
#include <unordered_map>
#include <string>

namespace Rendering {
	std::unordered_map<std::string, Material*> loadedMaterials;
}