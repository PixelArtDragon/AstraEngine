#include "Drawable3D.h"
#include "Rendering.h"

namespace Rendering {

	Drawable3D::Drawable3D()
	{
		Rendering::AddDrawable(this);
	}


	Drawable3D::~Drawable3D()
	{
		Rendering::RemoveDrawable(this);
	}
}