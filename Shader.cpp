#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include "Rendering.h"
#include "GLDebug.h"
#include "ShaderFileLoader.h"

namespace Rendering {

	Shader* Shader::defaultShader;

	Shader::Shader(std::string vertex_file, std::string fragment_file)
	{
		
		program = LoadShaderFile(vertex_file, fragment_file);

		//Cache uniform positions
		camera_uniform = glGetUniformLocation(program, "camera_transform");
		object_uniform = glGetUniformLocation(program, "object_transform");
		texture_uniform = glGetUniformLocation(program, "texture1");
	}

	void Shader::Load()
	{
		glUseProgram(program);
		Camera& camera = GetActiveCamera();

		glUniformMatrix4fv(camera_uniform, 1, GL_FALSE, glm::value_ptr(camera.GetProjection() * camera.GetView()));
		
	}

	void Shader::Load(Material * material)
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(texture_uniform, 0);
		if (material == nullptr || material->textures.size() < 1) {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, material->textures[0].texture_id);
		}
	}

	void Shader::Load(Drawable3D * drawable)
	{
		glUniformMatrix4fv(object_uniform, 1, GL_FALSE, glm::value_ptr(drawable->GetTransform()->matrix()));
	}

}
