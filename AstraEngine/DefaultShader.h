#pragma once
#include "Shader.h"

namespace Rendering {
	class DefaultShader : public Shader
	{
	public:
		DefaultShader();
		~DefaultShader();
		virtual void Load() override;
		virtual void Load(Material * material) override;
		virtual void Load(Drawable3D * drawable) override;
	};
}