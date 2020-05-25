#include "Vertex.h"

Rendering::Vertex::Vertex()
{
}

Rendering::Vertex::Vertex(glm::vec3 position)
{
	this->position = position;
}

Rendering::Vertex::Vertex(glm::vec3 position, glm::vec2 uv) {
	this->position = position;
	this->uv = uv;
}

Rendering::Vertex::Vertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal)
{
	this->position = position;
	this->uv = uv;
	this->normal = normal;
}
