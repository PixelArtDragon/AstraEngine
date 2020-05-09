#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace Rendering {
	struct Vertex
	{
		Vertex();
		Vertex(glm::vec3 position);
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
	};
}