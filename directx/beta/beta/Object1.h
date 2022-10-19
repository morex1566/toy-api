#pragma once
#include "Script.h"

class Object1 : public BaseScript
{
public:
	Object1();
	Object1(BaseGameObject*);
	~Object1();

public:
	void Start() override;
	void Update() override;

private:
	float rotation;
};

