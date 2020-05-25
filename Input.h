#pragma once
#include "Callback.h"
#include <unordered_map>
#include <unordered_set>
#include <glm\vec2.hpp>
#include <SFML\Window.hpp>

#define KEY_TYPE sf::Keyboard::Key
#define MOUSE_BUTTON sf::Mouse::Button

enum class InputType {
	Key_Pressed,
	Key_Released,
	Key_Down
};
namespace Input
{
	 void KeyPressed(KEY_TYPE key);
	 void KeyReleased(KEY_TYPE key);
	 void MouseClicked(MOUSE_BUTTON mouseButton);
	 void MouseReleased(MOUSE_BUTTON mouseButton);
	 void Update();

	 bool IsDown(KEY_TYPE key);
	 bool IsDown(MOUSE_BUTTON mouseButton);

	 extern glm::vec2 mousePosition;

	 void MouseMoved(int newXPos, int newYPosd);

	 void RegisterBinding(KEY_TYPE key, Callback* binding, InputType type);
	 void RegisterBinding(MOUSE_BUTTON mouseButton, Callback* binding, InputType type);
	 void RegisterMouseMotion(Callback* binding);
	
	
	 extern std::unordered_map<KEY_TYPE, Callback*> keyPressedBindings;
	 extern std::unordered_map<KEY_TYPE, Callback*> keyReleasedBindings;
	 extern std::unordered_map<KEY_TYPE, Callback*> keyDownBindings;
	 extern std::unordered_map<MOUSE_BUTTON, Callback*> mouseDownBindings;
	 extern std::unordered_map<MOUSE_BUTTON, Callback*> mousePressedBindings;
	 extern std::unordered_map<MOUSE_BUTTON, Callback*> mouseReleasedBindings;
	 extern Callback* mouseMotion;
};