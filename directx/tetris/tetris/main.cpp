////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include <memory>

#include "systemclass.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) 
{
	auto system = std::make_unique<SystemClass>();
	bool result;

	// Initialize and run the system object.
	result = system->Initialize();
	if(result)
	{
		system->Run();
	}

	// Shutdown and release the system object.
	system->Shutdown();

	return 0;
}