#pragma once
#include <glm/vec2.hpp>
#include "Rect.h"
#include "WindowType.h"

namespace Window {
	void Init();

	void Finish();

	bool IsOpen();

	void PollEvents();

	void ShowFrame();

	void Close();

	Rect GetWindowBounds();

	Rect GetViewport();

	glm::vec2 GetWindowSize();

	glm::vec2 NormalizeScreenCoordinates(glm::vec2 screen_coordinate);

	Window * GetWindowPointer();
}

