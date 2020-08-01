#include "LambdaUpdator.h"

Updating::LambdaUpdator::LambdaUpdator(std::function<void()> lambda)
{
	this->function = lambda;
}

void Updating::LambdaUpdator::Call()
{
	function();
}
