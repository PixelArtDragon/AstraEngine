#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>
#include "Texture.h"

namespace Rendering {
	struct Material
	{
	public:
		Material();
		~Material();
		std::vector<Texture> textures;
	};
}