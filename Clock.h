#pragma once
#include <chrono>

namespace Clock
{
	typedef std::chrono::high_resolution_clock::time_point timestamp;
	typedef std::chrono::seconds seconds;

	extern float deltaTime;
	void tick();
	void Init();
	extern float time_since_start;
	extern timestamp gameStart;
	extern timestamp lastTime;
	extern timestamp currentTime;

};

