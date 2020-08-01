#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace Rendering {

	constexpr unsigned int position_index = 0;
	constexpr unsigned int uv_index = 1;
	constexpr unsigned int normal_index = 2;
	constexpr unsigned int color_index = 3;


	struct Vertex
	{
		Vertex();
		Vertex(glm::vec3 position);
		Vertex(glm::vec3 position, glm::vec2 uv);
		Vertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal);
		Vertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal, glm::vec4 color);
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
		glm::vec4 color;
	};
}