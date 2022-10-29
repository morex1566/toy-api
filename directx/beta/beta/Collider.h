#pragma once
#include "Component.h"

class Collider : public BaseComponent
{
public:
	Collider(BaseGameObject*);
	~Collider();

public:
	void Start() override;
	void Update() override;

private:
};

