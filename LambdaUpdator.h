#pragma once
#include "Updator.h"
#include <functional>

namespace Updating {
	class LambdaUpdator : public Updator
	{
	public:
		std::function<void()> function;
		LambdaUpdator(std::function<void()> lambda);


		// Inherited via Updator
		virtual void Call() override;

	};
}