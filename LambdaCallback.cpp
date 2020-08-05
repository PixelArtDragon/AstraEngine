#include "LambdaCallback.h"

LambdaCallback::LambdaCallback(std::function<void()> function) : function(function)
{
}

void LambdaCallback::Call()
{
	function();
}
