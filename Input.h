#pragma once
#include "Callback.h"
#include <unordered_map>
#include <unordered_set>
#include <glm\vec2.hpp>
#include "KeyCodes.h"

typedef int MOUSE_BUTTON;

enum class InputType {
	Key_Pressed,
	Key_Released,
	Key_Down
};
namespace Input
{
	 void KeyPressed(KeyCode key);
	 void KeyReleased(KeyCode key);
	 void MouseClicked(MOUSE_BUTTON mouseButton);
	 void MouseReleased(MOUSE_BUTTON mouseButton);
	 void Update();

	 bool IsDown(KeyCode key);
	 bool IsDown(MOUSE_BUTTON mouseButton);

	 extern glm::vec2 mousePosition;

	 void MouseMoved(int newXPos, int newYPosd);

	 void RegisterBinding(KeyCode key, Callback* binding, InputType type);
	 void RegisterBinding(MOUSE_BUTTON mouseButton, Callback* binding, InputType type);
	 void RegisterMouseMotion(Callback* binding);
	
	
	 extern std::unordered_map<KeyCode, Callback*> keyPressedBindings;
	 extern std::unordered_map<KeyCode, Callback*> keyReleasedBindings;
	 extern std::unordered_map<KeyCode, Callback*> keyDownBindings;
	 extern std::unordered_map<MOUSE_BUTTON, Callback*> mouseDownBindings;
	 extern std::unordered_map<MOUSE_BUTTON, Callback*> mousePressedBindings;
	 extern std::unordered_map<MOUSE_BUTTON, Callback*> mouseReleasedBindings;
	 extern Callback* mouseMotion;
};