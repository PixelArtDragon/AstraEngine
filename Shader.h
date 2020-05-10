#pragma once
#include <glew/glew.h>
#include "Material.h"
#include <unordered_map>

namespace Rendering {
	class Drawable3D;
	class Shader {
	public:
		Shader(std::string vertex_file, std::string fragment_file);
		virtual void Load();
		virtual void Load(Material* material);
		virtual void Load(Drawable3D* drawable);
		static Shader* defaultShader;
	protected:
		GLuint program;
		GLuint camera_uniform;
		GLuint object_uniform;
	};
}