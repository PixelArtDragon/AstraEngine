#include "ShaderFileLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace Rendering {
	GLuint LoadShaderFile(std::string vertex_shader_file, std::string fragment_shader_file)
	{
		GLuint program;
		std::string	vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;


		try {
			vShaderFile.open(vertex_shader_file);
			fShaderFile.open(fragment_shader_file);
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
				std::cout << "ERROR compiling shader: " << vertex_shader_file.c_str() << std::endl << &shader_log[0] << std::endl;
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
				std::cout << "ERROR compiling shader: " << fragment_shader_file.c_str() << std::endl << &shader_log[0] << std::endl;
			}
		}

		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return program;
	}
}