#include "Rendering.h"
#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <map>
#include "Window.h"
#include <algorithm>
#include "GLDebug.h"
#include <glm/gtx/compatibility.hpp>

#include "UI.h"

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
	
	std::vector<Renderable*> renderables;
	std::vector<Drawable3D*> ordered_drawables;

	void Init() {
		glewExperimental = true;
		glewInit();

		rendering_options.window_bounds = Window::GetViewport();
		rendering_options.depth_enabled = true;
		rendering_options.depth_function = GL_LEQUAL;
		rendering_options.stencil_enabled = true;
		rendering_options.clear_depth = 1.0f;
		rendering_options.clear_color = glm::vec4(0.0, 0.5, 0.5, 0.0);
		rendering_options.clear_bits = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
		rendering_options.culling_enabled = true;
		rendering_options.cull_face = GL_BACK;



		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawBuffer(GL_BACK);
		glReadBuffer(GL_BACK);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
	void RenderRenderables() {
		for (size_t i = 0; i < renderables.size(); i++)
		{
			renderables[i]->Draw();
		}
	}
	void RenderFrame()
	{
		//glClearStencil(0xFF);
		//glDisable(GL_STENCIL_TEST);
		//glDisable(GL_FRAMEBUFFER_SRGB);
		if (light_source != nullptr) {
			light_source->BeginRender();
			for (size_t i = 0; i < ordered_drawables.size(); i++) {
				light_source->Render(ordered_drawables[i]);
			}
			light_source->EndRender();
		}
		//rendering_options.Apply();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		Rect viewport = Window::GetViewport();
		glViewport(0, 0, viewport.width, viewport.height);
		glClearColor(0.0f, 0.5f, 0.5f, 0.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glDepthMask(GL_TRUE);
		glEnable(GL_CULL_FACE);
		glEnable(GL_STENCIL_TEST);
		glCullFace(GL_BACK);
		glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		glDisable(GL_SAMPLE_COVERAGE);
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
		DrawDrawables();
		UI::Render();
		glDepthMask(GL_TRUE);

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
	void AddRenderable(Renderable* renderable) {
		renderables.push_back(renderable);
	}
	void RemoveRenderable(Renderable* renderable) {
		auto it = std::find(renderables.begin(), renderables.end(), renderable);
		if (it != renderables.end()) {
			renderables.erase(it);
		}
	}

	Camera & GetActiveCamera()
	{
		return *camera;
	}

	float getDepth(glm::vec2 screen_point)
	{
		GLfloat depth;
		glReadPixels((int)(screen_point.x), Window::GetWindowSize().y - (int)(screen_point.y), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		checkError();
		return (float)depth;
	}
	glm::vec3 ScreenPointToWorldPosition(glm::vec2 screen_point)
	{
		float z_depth = getDepth(screen_point);

		glm::vec2 normalizedScreenPoint = Window::NormalizeScreenCoordinates(screen_point);

		glm::mat4 inverse_transform = glm::inverse(camera->GetView()) * glm::inverse(camera->GetProjection());

		glm::vec4 p = inverse_transform * glm::vec4(normalizedScreenPoint, -1, 1);
		glm::vec4 q = inverse_transform * glm::vec4(normalizedScreenPoint, 1, 1);

		glm::vec4 world_vector =  glm::lerp(p, q, z_depth);

		return world_vector / world_vector.w;
	}
}