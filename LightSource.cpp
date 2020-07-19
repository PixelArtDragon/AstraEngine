#include "LightSource.h"
#include <glm/gtc/type_ptr.hpp>
#include "ShaderFileLoader.h"

namespace Rendering {
	Lightsource::Lightsource(std::string vertex_shader_file, std::string fragment_shader_file, size_t size)
	{
		this->_size = size;

		_render_options.window_bounds = Rect(0, 0, size, size);
		_render_options.depth_enabled = true;
		_render_options.clear_depth = 1.0f;
		_render_options.clear_bits = GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
		_render_options.culling_enabled = true;
		_render_options.cull_face = GL_FRONT;
		_render_options.depth_function = GL_LEQUAL;

		transform = new Transform();
		shadowBuffer = new ShadowBuffer(size);

		light_program = LoadShaderFile(vertex_shader_file, fragment_shader_file);

		light_uniform = glGetUniformLocation(light_program, "light_transform");
		object_uniform = glGetUniformLocation(light_program, "object_transform");
	}
	Lightsource::~Lightsource()
	{
		delete transform;
		delete shadowBuffer;
	}
	void Lightsource::BeginRender()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer->fbo);
		_render_options.Apply();
		glUseProgram(light_program);
		light_transformation = glm::ortho<float>(-5.0, 5.0, -5.0, 5.0, -10, 20.0) * transform->matrix();
		//light_transformation = glm::perspective(45.0f, 1.0f, 0.1f, 10.0f) * glm::inverse(transform->matrix());
		glUniformMatrix4fv(light_uniform, 1, GL_FALSE, glm::value_ptr(light_transformation));
	}
	void Lightsource::Render(Drawable3D * drawable)
	{
		glUniformMatrix4fv(object_uniform, 1, GL_FALSE, glm::value_ptr(drawable->GetTransform()->matrix()));
		drawable->Draw();
	}
	void Lightsource::EndRender()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}