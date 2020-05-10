#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering.h"

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

		const char * fShaderCode = fragmentCode.c_str();
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);

		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);
		
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);


		//Cache uniform positions
		camera_uniform = glGetUniformLocation(program, "camera_transform");
		object_uniform = glGetUniformLocation(program, "object_transform");
	}

	void Shader::Load()
	{
		glUseProgram(program);
		Camera& camera = GetActiveCamera();

		glUniformMatrix4fv(camera_uniform, 1, GL_FALSE, glm::value_ptr(camera.GetProjection() * camera.GetView()));
		
	}

	void Shader::Load(Material * material)
	{
	}

	void Shader::Load(Drawable3D * drawable)
	{
		glUniformMatrix4fv(object_uniform, 1, GL_FALSE, glm::value_ptr(drawable->GetTransform()->matrix()));
	}

}
