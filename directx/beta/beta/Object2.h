#pragma once
#include "Script.h"

class Object2 : public BaseScript
{
public:
	Object2();
	Object2(BaseGameObject*);
	~Object2();

public:
	void Start() override;
	void Update() override;

private:
	float rotation;
};

