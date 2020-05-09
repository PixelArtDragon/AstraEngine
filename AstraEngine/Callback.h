#pragma once
class Callback
{
public:
	Callback();
	virtual ~Callback() = 0;
	virtual void Call() = 0;
};

