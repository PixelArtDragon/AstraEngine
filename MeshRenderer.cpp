#include "MeshRenderer.h"
#include "GLDebug.h"

namespace Rendering {

	MeshRenderer::MeshRenderer()
	{
		_transform = new Transform();
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::uv)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::normal)));
		

	}


	MeshRenderer::~MeshRenderer()
	{
		delete _transform;
	}
	void MeshRenderer::Draw()
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(VertexIndex), triangles.data(), GL_STATIC_DRAW);
		glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT, (void*)0);
	}
	Transform * MeshRenderer::GetTransform()
	{
		return _transform;
	}
}