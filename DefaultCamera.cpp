#include "DefaultCamera.h"

namespace Rendering {

	DefaultCamera::DefaultCamera()
	{
		transform = new Transform();
	}


	DefaultCamera::~DefaultCamera()
	{
		delete transform;
	}
	Transform * DefaultCamera::GetTransform()
	{
		return transform;
	}
}