#pragma once
#include "Drawable3D.h"
#include "Vertex.h"

namespace Rendering {
	typedef unsigned int VertexIndex;
	class MeshRenderer : public Drawable3D
	{
	public:
		MeshRenderer();
		MeshRenderer(std::string filename);
		~MeshRenderer();

		// Inherited via Drawable3D
		virtual void Draw() override;
		virtual Transform * GetTransform() override;

		std::vector<Vertex> vertices;
		std::vector<VertexIndex> triangles;
		std::vector<GLuint> textures;

		bool triangles_streamed;
		bool vertices_streamed;
	private:

		GLuint vao;
		GLuint vbo;
		GLuint ebo;
		Transform * _transform;
	};
}
