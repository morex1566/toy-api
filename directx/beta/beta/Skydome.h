#pragma once
#include "GameObject.h"

class Skydome : public BaseGameObject
{
public:
	Skydome(D3DClass*, HWND);
	Skydome(const Skydome&);
	~Skydome() override;

public:
	void Start() override;
	void Update() override;
};

