#include "Rendering.h"
#include <string>
#include <unordered_map>
#include <map>
#include <glew/glew.h>
#include <algorithm>
#include "GLDebug.h"
#include "Window.h"

namespace Rendering {

	Camera* camera;
	Lightsource* light_source;
	RenderOptions rendering_options;

	bool compareDrawables(Drawable3D* lhs, Drawable3D* rhs) {
		if (lhs->material == rhs->material) {
			return lhs->shader < rhs->shader;
		}
		else {
			return lhs->material < rhs->material;
		}
	}

	//Canonical storage of rendering objects
	std::unordered_map<std::string, Shader*> shaders;
	std::unordered_map<std::string, Material*> materials;
	std::unordered_map<std::string, Drawable3D*> drawables;

	std::vector<Drawable3D*> ordered_drawables;

	void Init() {
		glewExperimental = true;
		glewInit();

		rendering_options.window_bounds = Window::GetViewport();
		rendering_options.depth_enabled = true;
		rendering_options.depth_function = GL_LEQUAL;
		rendering_options.clear_depth = 1.0f;
		rendering_options.clear_color = glm::vec4(0.0, 0.5, 0.5, 0.0);
		rendering_options.clear_bits = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
		rendering_options.culling_enabled = true;
		rendering_options.cull_face = GL_BACK;



		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		checkError();
	}
	void Reshape(glm::vec2 newDimensions)
	{
	}


	void DrawDrawables() {
		if (ordered_drawables.size() == 0) {
			return;
		}
		ordered_drawables[0]->shader->Load();
		ordered_drawables[0]->shader->Load(ordered_drawables[0]->material);
		ordered_drawables[0]->shader->Load(ordered_drawables[0]);
		ordered_drawables[0]->Draw();
		for (size_t i = 1; i < ordered_drawables.size(); i++)
		{
			if (ordered_drawables[i]->material != ordered_drawables[i - 1]->material) {
				if (ordered_drawables[i]->shader != ordered_drawables[i - 1]->shader) {
					ordered_drawables[i]->shader->Load();
				}
				ordered_drawables[i]->shader->Load(ordered_drawables[i]->material);
			}
			ordered_drawables[i]->shader->Load(ordered_drawables[i]);
			ordered_drawables[i]->Draw();
		}
	}
	void RenderFrame()
	{
		if (light_source != nullptr) {
			light_source->BeginRender();
			for (size_t i = 0; i < ordered_drawables.size(); i++) {
				light_source->Render(ordered_drawables[i]);
			}
			light_source->EndRender();
		}
		rendering_options.Apply();
		DrawDrawables();
	}
	void AddDrawable(Drawable3D * drawable)
	{
		drawables[drawable->name] = drawable;
		auto it = std::upper_bound(ordered_drawables.begin(), ordered_drawables.end(), drawable, compareDrawables);
		ordered_drawables.insert(it, drawable);
	}

	void RemoveDrawable(Drawable3D * drawable)
	{
		drawables.erase(drawable->name);
		auto it = std::find(ordered_drawables.begin(), ordered_drawables.end(), drawable);
		if (it != ordered_drawables.end()) {
			ordered_drawables.erase(it);
		}
	}

	Camera & GetActiveCamera()
	{
		return *camera;
	}
}