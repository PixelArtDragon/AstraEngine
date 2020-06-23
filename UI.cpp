#include "UI.h"
#include <GL/glew.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "Window.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <unordered_set>


namespace UI {

	std::unordered_set<Updating::Updator*> updators;

	void Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO &io = ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(Window::GetWindowPointer(), true);
		ImGui_ImplOpenGL3_Init("#version 430 core");
		ImGui::StyleColorsDark();
	}

	void Update()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		std::vector<Updating::Updator*> finishedUpdators;

		for (auto updator : updators) {
			if (!updator->is_done) {
				updator->Call();
			}
			if (updator->is_done) {
				finishedUpdators.push_back(updator);
			}
		}
		for (auto updator : finishedUpdators) {
			updators.erase(updator);
			delete updator;
		}	

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void AddUpdator(Updating::Updator * updator)
	{
		updators.emplace(updator);
	}
}