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

	Rect GetViewport();

	glm::vec2 GetWindowSize();

	glm::vec2 NormalizeScreenCoordinates(glm::vec2 screen_coordinate);
}

