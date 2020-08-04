#include "Material.h"

namespace Rendering {

	Material::Material()
	{
	}

	Material::Material(Texture texture)
	{
		this->textures.push_back(texture);
	}


	Material::~Material()
	{
	}
}