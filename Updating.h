#pragma once
#include <unordered_set>
#include "Updator.h"

namespace Updating {
	extern std::unordered_set<Updator*> updators;
	void Update();
}