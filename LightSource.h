#pragma once
#include "Transform.h"
#include "ShadowBuffer.h"
#include <string>

namespace Rendering {
	class Lightsource {
	public:
		Lightsource(std::string vertex_shader_file, std::string fragment_shader_file);
		~Lightsource();
		void BeginRender();
		void Render(Drawable3D* drawable);
		void EndRender();
		glm::mat4 light_transformation;
		GLuint light_program;
		Transform* transform;
		ShadowBuffer* shadowBuffer;

	private:
		GLuint light_uniform;
		GLuint object_uniform;
	};
}