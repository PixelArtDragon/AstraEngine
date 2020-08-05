#pragma once
#include "Callback.h"
#include <functional>

class LambdaCallback : public Callback
{
public:
	LambdaCallback(std::function<void()> function);
	std::function<void()> function;

	// Inherited via Updator
	virtual void Call() override;
};