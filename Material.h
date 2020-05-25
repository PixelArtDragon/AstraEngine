#pragma once
#include <string>
#include <vector>
#include "Texture.h"
#include <glew/glew.h>

namespace Rendering {
	struct Material
	{
	public:
		Material();
		~Material();
		std::vector<Texture> textures;
	};
}