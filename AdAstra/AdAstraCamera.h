#pragma once
#include "Camera.h"

class AdAstraCamera : public Rendering::Camera
{
public:
	AdAstraCamera();
	~AdAstraCamera();
private:
	Transform * _transform;
};