#pragma once
class System
{
public:
	System();
	~System();

	void Start();
	void Update();
	void Close();

private:
	bool isRunning;
};

