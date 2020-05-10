#pragma once
#include <glm/vec2.hpp>
#include "Callback.h"
#include <SFML/Window/Event.hpp>

namespace Input {
	enum class InputType {
		Key_Pressed,
		Key_Released,
		Key_Down
	};
	void Init();

	void KeyPressed(sf::Keyboard::Key key);
	void KeyReleased(sf::Keyboard::Key key);
	void MouseClicked(sf::Mouse::Button mouseButton);
	void MouseReleased(sf::Mouse::Button mouseButton);

	glm::vec2 GetMousePosition();
}

