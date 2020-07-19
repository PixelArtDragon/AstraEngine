#include "Engine.h"
#include "Rendering.h"
#include "Window.h"
#include "UI.h"
#include "Input.h"
#include "DefaultCamera.h"
#include "Clock.h"
#include "Updating.h"



namespace Engine {
	void Init() {
		Window::Init();
		UI::Init();
		Rendering::Init();
		Clock::Init();
	}
	void Prerun() {
		if (Rendering::camera == nullptr) {
			Rendering::camera = new Rendering::DefaultCamera();
		}
	}
	void Run()
	{
		Prerun();
		while (Window::IsOpen())
		{
			Clock::tick();
			Window::PollEvents();
			Input::Update();
			Updating::Update();
			UI::Update();
			Rendering::RenderFrame();
			Window::ShowFrame();
		}
	}

	void Finish() {
		UI::Finish();
		Window::Finish();
	}
}
