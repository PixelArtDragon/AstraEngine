#pragma once
#include "Drawable3D.h"

namespace Rendering {
	class Triangle : Drawable3D
	{
	public:
		Triangle();
		~Triangle();

		// Inherited via Drawable3D
		virtual Transform * GetTransform() override;

		// Inherited via Drawable3D
		virtual void Draw() override;
	private:
		Transform * _transform;

	};
}

