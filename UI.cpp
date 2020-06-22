#include "UI.h"
#include <GL/glew.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "Window.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void UI::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(Window::GetWindowPointer(), true);
	ImGui_ImplOpenGL3_Init("#version 430 core");
	ImGui::StyleColorsDark();
}

void UI::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Demo Window");
	ImGui::Button("Hello!");
	ImGui::End();

	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
