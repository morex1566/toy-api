#pragma once
#include <string>

#include "GameObject.h"
#include "d3dclass.h"

class Object : public BaseGameObject
{
public:
	Object(D3DClass*);
	Object(const Object&);
	~Object() override;

public:
	void Update() override;

private:
	void updateComponent();
	void updateScript();
};

