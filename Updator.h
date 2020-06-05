#pragma once
#include "Callback.h"

namespace Updating {
	class Updator : public Callback
	{
	public:
		bool is_done = false;
	};
}