#include "Engine.h"
#include "Rendering.h"
#include "MeshRenderer.h"
#include "LoadedShaders.h"
#include "PerspectiveCamera.h"

int main() {

	Engine::Init();

	Rendering::loadedShaders["default"] = new Rendering::Shader("vertex_shader.glsl", "fragment_shader.glsl");

	Rendering::MeshRenderer* test = new Rendering::MeshRenderer();

	test->name = "Test";
	test->vertices.push_back(Rendering::Vertex(glm::vec3(-0.5, -0.5, 0)));
	test->vertices.push_back(Rendering::Vertex(glm::vec3(0.5, -0.5, 0)));
	test->vertices.push_back(Rendering::Vertex(glm::vec3(-0.5, 0.5, 0)));
	test->vertices.push_back(Rendering::Vertex(glm::vec3(0.5, 0.5, 0)));
	test->triangles.push_back(0);
	test->triangles.push_back(1);
	test->triangles.push_back(2);
	test->triangles.push_back(2);
	test->triangles.push_back(1);
	test->triangles.push_back(3);
	test->shader = Rendering::loadedShaders["default"];

	Rendering::camera = new Rendering::PerspectiveCamera();



	Rendering::AddDrawable(test);

	Engine::Run();

	Engine::Finish();

	return 0;
}