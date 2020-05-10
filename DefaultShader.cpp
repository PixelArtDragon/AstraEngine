#include "DefaultShader.h"

namespace Rendering {

	DefaultShader::DefaultShader()
	{
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, "version, 
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	}


	DefaultShader::~DefaultShader()
	{
	}

	void DefaultShader::Load()
	{
		Shader::Load();
	}

	void DefaultShader::Load(Material * material)
	{
	}

	void DefaultShader::Load(Drawable3D * drawable)
	{
	}

}