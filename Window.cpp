#include "Window.h"
#include <SFML/Graphics.hpp>
#include "WindowUtils.h"
#include "Input.h"


namespace Window {
	sf::RenderWindow* _sfWindow;

	void Init() {
		sf::ContextSettings settings;
		settings.majorVersion = 4;
		settings.minorVersion = 5;
		settings.depthBits = 24;
		_sfWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
	}

	bool IsOpen()
	{
		return _sfWindow->isOpen();
	}

	void PollEvents()
	{
		sf::Event event;
		while (_sfWindow->pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				Close();
				break;
			case sf::Event::Resized:
				//Rendering::Reshape(event.size.width, event.size.height);
				break;
			case sf::Event::KeyPressed:
				Input::KeyPressed(event.key.code);
				break;
			case sf::Event::KeyReleased:
				Input::KeyReleased(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//Input::MouseMoved(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				Input::MouseClicked(event.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:
				break;
			default:
				break;
			}
		}
	}

	void ShowFrame()
	{
		_sfWindow->display();
	}

	void Close()
	{
		_sfWindow->close();
	}

	glm::vec2 GetMousePosition()
	{
		return SFMLtoGLM(sf::Mouse::getPosition(*_sfWindow));
	}
	Rect GetWindowBounds()
	{
		Rect rect;
		//TODO: add definition;
		//glm::vec3 size(_sfWindow->getSize());
		return rect;
	}
	glm::vec2 GetWindowSize()
	{
		return SFMLtoGLM(_sfWindow->getSize());
	}
}