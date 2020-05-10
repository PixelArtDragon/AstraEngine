#pragma once
#include <glm/vec2.hpp>
#include "Rect.h"

namespace Window {
	void Init();

	bool IsOpen();

	void PollEvents();

	void ShowFrame();

	void Close();

	glm::vec2 GetMousePosition();

	Rect GetWindowBounds();

	glm::vec2 GetWindowSize();
}

