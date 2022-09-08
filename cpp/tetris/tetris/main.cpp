#include <memory>

#include "System.h"

void main()
{
	auto system = std::make_unique<System>();

	system->Start();
	system->Update();
	system->Close();

	return;
}