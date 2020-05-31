#pragma once
#include "Transform.h"
#include "ShadowBuffer.h"
#include "RenderOptions.h"
#include <string>

namespace Rendering {
	class Lightsource {
	public:
		Lightsource(std::string vertex_shader_file, std::string fragment_shader_file, size_t map_size);
		~Lightsource();
		void BeginRender();
		void Render(Drawable3D* drawable);
		void EndRender();
		glm::mat4 light_transformation;
		GLuint light_program;
		Transform* transform;
		ShadowBuffer* shadowBuffer;
		void resize(size_t new_size);
		size_t size();
	private:
		RenderOptions _render_options;
		size_t _size;
		GLuint light_uniform;
		GLuint object_uniform;
	};
}