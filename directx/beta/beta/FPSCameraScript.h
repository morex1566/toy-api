#pragma once
#include "Script.h"	

class FPSCameraScript : public BaseScript
{
public:
	FPSCameraScript();
	FPSCameraScript(BaseGameObject*);
	~FPSCameraScript() override;

	void Start() override;
	void Update() override;

private:
	void handleInput();

public:
	bool m_Enable;
	float m_RotateSpeed;
};

