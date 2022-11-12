#pragma once
#include <string>

#include "GameObject.h"
#include "d3dclass.h"

class Foliage : public BaseGameObject
{
public:
	Foliage(D3DClass*, HWND);
	Foliage(const Foliage&);
	~Foliage() override;

public:
	void Start() override;
	void Update() override;
};

