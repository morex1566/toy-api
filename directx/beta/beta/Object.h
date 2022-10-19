#pragma once
#include <string>

#include "GameObject.h"
#include "d3dclass.h"

class Object : public BaseGameObject
{
public:
	Object(D3DClass*, HWND);
	Object(const Object&);
	~Object() override;

public:
	void Start() override;
	void Update() override;
	void Render(vector<BaseGameObject*>, Camera*) override;

private:
};

