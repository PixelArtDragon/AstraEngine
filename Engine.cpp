#include "Engine.h"
#include "Window.h"
#include "Input.h"
#include "Rendering.h"
#include "DefaultCamera.h"

namespace Engine {
	void Init() {
		Window::Init();
		Rendering::Init();
		Input::Init();
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
			Window::PollEvents();
			Rendering::RenderFrame();
			Window::ShowFrame();
		}
	}

	void Finish() {

	}
}
