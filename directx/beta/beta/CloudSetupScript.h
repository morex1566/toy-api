#pragma once
#include "Script.h"
#include "d3dclass.h"

class Camera;
class Texture;

class SkyplaneSetupScript : public BaseScript
{
public:
	SkyplaneSetupScript();
	SkyplaneSetupScript(Camera*);
	SkyplaneSetupScript(BaseGameObject*);
	~SkyplaneSetupScript() override;

public:
	void Start() override;
	void Update() override;

public:
	float GetTranslation(int);
	float GetBrightness();
	ID3D11ShaderResourceView* GetTexture(int);


private:
	void destroyMember();

private:
	Texture* m_texture[2];
	Camera* m_mainCamera;
	float m_brightness;
	float m_translationSpeed[4];
	float m_textureTranslation[4];

};

