#pragma once
#include <glm/vec2.hpp>
#include "Callback.h"
#include "Key.h"
#include "MouseButton.h"

namespace Input {
	enum class InputType {
		Key_Pressed,
		Key_Released,
		Key_Down
	};
	void Init();

	void KeyPressed(Key key);
	void KeyReleased(Key key);
	void MouseClicked(MouseButton mouseButton);
	void MouseReleased(MouseButton mouseButton);

	glm::vec2 GetMousePosition();
}

