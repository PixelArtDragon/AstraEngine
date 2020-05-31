#include "LightSource.h"
#include <glm/gtc/type_ptr.hpp>
#include "ShaderFileLoader.h"

namespace Rendering {
	Lightsource::Lightsource(std::string vertex_shader_file, std::string fragment_shader_file)
	{
		transform = new Transform();
		shadowBuffer = new ShadowBuffer(2048);

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
		glViewport(0, 0, 2048, 2048);
		glClearDepth(1.0f);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);
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