#pragma once

#include "GameObject.h"
#include "d3dclass.h"

class Cloud : public BaseGameObject
{
public:
	Cloud(D3DClass*, HWND);
	Cloud(const Cloud&);
	~Cloud() override;

public:
	void Start() override;
	void Update() override;

private:
	float m_textureTranslation[4];
	float m_translationSpeed[4];
};

