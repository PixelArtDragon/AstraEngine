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
		Rendering::Init();
		UI::Init();
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
			Rendering::RenderFrame();
			UI::Update();
			Window::ShowFrame();
		}
	}

	void Finish() {
		Window::Finish();
	}
}
