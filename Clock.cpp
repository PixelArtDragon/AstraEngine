#include "Clock.h"

using namespace std::chrono;

namespace Clock {
	float deltaTime = 0.166666666666666667f; //initialize to 1/60 of a second
	timestamp gameStart;
	timestamp lastTime;
	timestamp currentTime;


	void tick()
	{
		//Set the old current to the previous fbo, set the new current to be now
		lastTime = currentTime;
		currentTime = high_resolution_clock::now();
		duration<float> myDeltaTime = currentTime - lastTime;
		deltaTime = myDeltaTime.count();
	}

	void Init()
	{
		gameStart = high_resolution_clock::now();
		currentTime = gameStart;
	}
}