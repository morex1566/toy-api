#pragma once
#include "GameObject.h"

class Terrain : public BaseGameObject
{
public:
	Terrain(D3DClass*, HWND);
	Terrain(const Terrain&);
	~Terrain() override;

public:
	void Start() override;
	void Update() override;

public:
	Terrain* SetWidthAndHeight(int width, int height);

private:
	int m_width;
	int m_height;
};

