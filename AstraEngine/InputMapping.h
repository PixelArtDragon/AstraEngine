#pragma once
#include <string>
#include <unordered_set>
#include "Callback.h"

namespace Input {

	class InputMapping
	{
	public:
		InputMapping();
		~InputMapping();

		std::unordered_set<Callback*> callbacks;
	};

}