#pragma once
namespace Engine
{
	//Init creates all the necessary resources that are required for any pre-run initialization
	void Init();

	//Finalizes any pre-init and starts the main loop
	void Run();

	//Deletes any engine-related resources
	void Finish();
};

