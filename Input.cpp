#include "Input.h"
#include "Engine.h"


namespace Input {
	glm::vec2 mousePosition;

	std::unordered_map<KEY_TYPE, Callback*> keyPressedBindings;
	std::unordered_map<KEY_TYPE, Callback*> keyReleasedBindings;
	std::unordered_map<KEY_TYPE, Callback*> keyDownBindings;
	std::unordered_map<MOUSE_BUTTON, Callback*> mouseDownBindings;
	std::unordered_map<MOUSE_BUTTON, Callback*> mousePressedBindings;
	std::unordered_map<MOUSE_BUTTON, Callback*> mouseReleasedBindings;
	Callback* mouseMotion;
}


void Input::KeyPressed(KEY_TYPE key)
{
	auto func = keyPressedBindings.find(key);
	if (func != keyPressedBindings.end()) {
		func->second->Call();
	}
	//downKeys.emplace(key);
}
void Input::KeyReleased(KEY_TYPE key)
{
	auto func = keyReleasedBindings.find(key);
	if (func != keyReleasedBindings.end()) {
		func->second->Call();
	}
	//downKeys.erase(key);
}

void Input::MouseClicked(MOUSE_BUTTON mouseButton)
{
	auto func = mousePressedBindings.find(mouseButton);
	if (func != mousePressedBindings.end()) {
		func->second->Call();
	}
}

void Input::MouseReleased(MOUSE_BUTTON mouseButton)
{
	auto func = mouseReleasedBindings.find(mouseButton);
	if (func != mouseReleasedBindings.end()) {
		func->second->Call();
	}
}


void Input::Update()
{
	for (auto keyBinding : keyDownBindings) {
		if (sf::Keyboard::isKeyPressed(keyBinding.first)) {
			keyBinding.second->Call();
		}
	}
	for (auto mouseBinding : mouseDownBindings) {
		if (sf::Mouse::isButtonPressed(mouseBinding.first)) {
			mouseBinding.second->Call();
		}
	}
}

bool Input::IsDown(KEY_TYPE key)
{
	return sf::Keyboard::isKeyPressed(key);
}

bool Input::IsDown(MOUSE_BUTTON mouseButton)
{
	return sf::Mouse::isButtonPressed(mouseButton);
}

void Input::MouseMoved(int newXPos, int newYPos)
{
	mousePosition = glm::vec2(newXPos, newYPos);
	if (mouseMotion != nullptr) {
		mouseMotion->Call();
	}
}

void Input::RegisterBinding(KEY_TYPE key, Callback* binding, InputType type)
{
	switch (type) {
	case InputType::Key_Down:
		keyDownBindings[key] = binding;
		break;
	case InputType::Key_Pressed:
		keyPressedBindings[key] = binding;
		break;
	case InputType::Key_Released:
		keyReleasedBindings[key] = binding;
		break;
	}
}

void Input::RegisterBinding(MOUSE_BUTTON mouseButton, Callback * binding, InputType type)
{
	switch (type) {
	case InputType::Key_Down:
		mouseDownBindings[mouseButton] = binding;
		break;
	case InputType::Key_Pressed:
		mousePressedBindings[mouseButton] = binding;
		break;
	case InputType::Key_Released:
		mouseReleasedBindings[mouseButton] = binding;
		break;
	}
}

void Input::RegisterMouseMotion(Callback * binding) {
	mouseMotion = binding;
}
