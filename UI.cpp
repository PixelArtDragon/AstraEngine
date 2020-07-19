#include "UI.h"
#include <GL/glew.h>
#include "Window.h"
#include <unordered_set>
#include <NoesisPCH.h>
#include <NsApp/ThemeProviders.h>
#include <NsRender/GLFactory.h>
#include "Clock.h"
#include "Rendering.h"
#include <iostream>

//#include "OpenGLState.h"

namespace UI {

	Noesis::Ptr<Noesis::IView> view;

	std::unordered_set<Updating::Updator*> updators;

	void TestClick();

	void Init()
	{
		Noesis::SetLogHandler([](const char*, uint32_t, uint32_t level, const char*, const char* msg)
		{
			// [TRACE] [DEBUG] [INFO] [WARNING] [ERROR]
			const char* prefixes[] = { "T", "D", "I", "W", "E" };
			printf("[NOESIS/%s] %s\n", prefixes[level], msg);
		});
		Noesis::GUI::Init(NS_LICENSE_NAME, NS_LICENSE_KEY);

		//Noesis::GUI::SetXamlProvider(Noesis::MakePtr<LocalXamlProvider>("."));
		//Noesis::GUI::SetFontProvider(MakePtr<LocalFontProvider>("."));
		//Noesis::GUI::SetTextureProvider(MakePtr<LocalTextureProvider>("."));

		const char* fonts[] = { "Fonts/#PT Root UI", "Arial", "Segoe UI Emoji" };

		Noesis::GUI::SetFontFallbacks(fonts, 3);

		NoesisApp::SetThemeProviders();
		Noesis::GUI::LoadApplicationResources("Theme/NoesisTheme.DarkBlue.xaml");
		
		Noesis::GUI::SetFontDefaultProperties(15.0f, Noesis::FontWeight_Normal, Noesis::FontStretch_Normal, Noesis::FontStyle_Normal);

		Noesis::Ptr<Noesis::Grid> xaml(Noesis::GUI::ParseXaml<Noesis::Grid>(R"(
        <Grid
			xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
			xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml">

			<Button x:Name="Button1" Content="Button" HorizontalAlignment="Left" Margin="10,10,0,0" VerticalAlignment="Top" Width="75"/>

		</Grid>
		)"));


		view = Noesis::GUI::CreateView(xaml);

		Noesis::Button* button = view->GetContent()->FindName<Noesis::Button>("Button1");
		button->Click() += [](Noesis::BaseComponent* sender, const Noesis::RoutedEventArgs& args) {
			TestClick();
		};

		Rect viewport = Window::GetViewport();
		view->SetSize(viewport.width, viewport.height);
		view->GetRenderer()->Init(NoesisApp::GLFactory::CreateDevice());
	}

	void TestClick() {
		std::cout << "Click!" << std::endl;
	}

	void Update()
	{
		view->Update(Clock::time_since_start);

		view->GetRenderer()->UpdateRenderTree();

		view->GetRenderer()->RenderOffscreen();
	}

	void AddUpdator(Updating::Updator * updator)
	{
		updators.emplace(updator);
	}
	void Render()
	{
		view->GetRenderer()->Render();
	}
	void Finish()
	{
		view->GetRenderer()->Shutdown();
		view.Reset();
		Noesis::GUI::Shutdown();
	}

	inline Noesis::MouseButton getMouseButton(MOUSE_BUTTON button) {
		switch (button)
		{
		case 0:
			return Noesis::MouseButton::MouseButton_Left;
			break;
		case 1:
			return Noesis::MouseButton::MouseButton_Right;
		case 2:
			return Noesis::MouseButton::MouseButton_Middle;
			break;
		default:
			break;
		}
	}

	bool MouseButtonAction(int x, int y, MOUSE_BUTTON button, InputType input_type)
	{
		switch (input_type)
		{
		case InputType::Key_Pressed:
			return view->MouseButtonDown(x, y, getMouseButton(button));
		case InputType::Key_Released:
			return view->MouseButtonUp(x, y, getMouseButton(button));
		default:
			break;
		}
	}
	bool MouseMove(int x, int y)
	{
		return view->MouseMove(x, y);
	}
	bool MouseWheel(int x, int y, int wheelRotation)
	{
		return false;
	}
	bool MouseHWheel(int x, int y, int wheelRotation)
	{
		return false;
	}
}