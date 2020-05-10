#pragma once
#include "Transform.h"
#include "Material.h"
#include "Shader.h"
#include <string>

namespace Rendering {
	class Drawable3D
	{
	public:
		Drawable3D();
		virtual ~Drawable3D();
		virtual void Draw() = 0;
		virtual Transform * GetTransform() = 0;
		Material* material;
		Shader* shader;
		std::string name;
	};
}