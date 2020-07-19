#pragma once
#include "Updator.h"
#include "InputType.h"


namespace UI {
	void Init();
	void Update();
	void AddUpdator(Updating::Updator* updator);
	void Render();
	void Finish();

	//Input functions
	bool MouseButtonAction(int x, int y, MOUSE_BUTTON button, InputType input_type);
	bool MouseMove(int x, int y);
	bool MouseWheel(int x, int y, int wheelRotation);
	bool MouseHWheel(int x, int y, int wheelRotation);
};

