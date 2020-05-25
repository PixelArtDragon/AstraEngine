#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering.h"
#include "GLDebug.h"

namespace Rendering {

	Shader* Shader::defaultShader;

	Shader::Shader(std::string vertex_file, std::string fragment_file)
	{
		std::string	vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;


		try {
			vShaderFile.open(vertex_file);
			fShaderFile.open(fragment_file);
			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char * vShaderCode = vertexCode.c_str();
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		GLint success = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			int info_log_length = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &info_log_length);
			if (info_log_length != 0) {
				std::vector<char> shader_log(info_log_length);
				glGetShaderInfoLog(vertexShader, info_log_length, NULL, &shader_log[0]);
				std::cout << "ERROR compiling shader: " << vertex_file.c_str() << std::endl << &shader_log[0] << std::endl;
			}
		}

		const char * fShaderCode = fragmentCode.c_str();
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			int info_log_length = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &info_log_length);
			if (info_log_length != 0) {
				std::vector<char> shader_log(info_log_length);
				glGetShaderInfoLog(fragmentShader, info_log_length, NULL, &shader_log[0]);
				std::cout << "ERROR compiling shader: " << vertex_file.c_str() << std::endl << &shader_log[0] << std::endl;
			}
		}

		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);
		
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);


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
