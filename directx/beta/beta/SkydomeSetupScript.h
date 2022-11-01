#pragma once
#include "Script.h"	

class Camera;

class SkydomeSetupScript : public BaseScript
{
public:
	SkydomeSetupScript();
	SkydomeSetupScript(Camera*);
	SkydomeSetupScript(BaseGameObject*);
	~SkydomeSetupScript() override;

public:
	void Start() override;
	void Update() override;

public:
	XMVECTOR GetApexColor();
	XMVECTOR GetCenterColor();
	void SetApexColor(XMVECTOR);
	void SetCenterColor(XMVECTOR);

private:
	Camera* m_mainCamera;
	XMVECTOR m_apexColor;
	XMVECTOR m_centerColor;
	
};

