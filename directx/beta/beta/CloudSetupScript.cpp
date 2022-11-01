#include "CloudSetupScript.h"
#include "cameraclass.h"
#include "textureclass.h"

SkyplaneSetupScript::SkyplaneSetupScript()
{
	m_Name = "SkyplaneSetupScript";
}

SkyplaneSetupScript::SkyplaneSetupScript(Camera* camera)
{
	m_Name = "SkyplaneSetupScript";
	m_mainCamera = camera;
}

SkyplaneSetupScript::SkyplaneSetupScript(BaseGameObject* gameObject)
	: BaseScript(gameObject)
{
	m_Name = "SkyplaneSetupScript";
}

SkyplaneSetupScript::~SkyplaneSetupScript()
{
	destroyMember();
}

void SkyplaneSetupScript::Start()
{
	m_texture[0] = new Texture(m_GameObject, "./resources/cloud001.dds");
	m_texture[1] = new Texture(m_GameObject, "./resources/cloud002.dds");

	XMFLOAT3 cameraPosition = m_mainCamera->GetTransform()->GetPosition();
	m_GameObject->GetTransform()->TranslateAt(cameraPosition);

	m_brightness = 0.65f;

	m_translationSpeed[0] = 0.0003f; 
	m_translationSpeed[1] = 0.0f; 
	m_translationSpeed[2] = 0.00015f; 
	m_translationSpeed[3] = 0.0f; 

	m_textureTranslation[0] = 0.0f;
	m_textureTranslation[1] = 0.0f;
	m_textureTranslation[2] = 0.0f;
	m_textureTranslation[3] = 0.0f;
}

void SkyplaneSetupScript::Update()
{
	// move cloud texture
	m_textureTranslation[0] += m_translationSpeed[0];
	m_textureTranslation[1] += m_translationSpeed[1];
	m_textureTranslation[2] += m_translationSpeed[2];
	m_textureTranslation[3] += m_translationSpeed[3];

	// cliping
	if (m_textureTranslation[0] > 1.0f) { m_textureTranslation[0] -= 1.0f; }
	if (m_textureTranslation[1] > 1.0f) { m_textureTranslation[1] -= 1.0f; }
	if (m_textureTranslation[2] > 1.0f) { m_textureTranslation[2] -= 1.0f; }
	if (m_textureTranslation[3] > 1.0f) { m_textureTranslation[3] -= 1.0f; }

	if (m_mainCamera)
	{
		XMFLOAT3 cameraPosition = m_mainCamera->GetTransform()->GetPosition();

		m_GameObject->GetTransform()->TranslateAt(cameraPosition);
	}
}

float SkyplaneSetupScript::GetTranslation(int index)
{
	return m_textureTranslation[index];
}

float SkyplaneSetupScript::GetBrightness()
{
	return m_brightness;
}

ID3D11ShaderResourceView* SkyplaneSetupScript::GetTexture(int index)
{
	return m_texture[index]->GetTexture();
}

void SkyplaneSetupScript::destroyMember()
{
	if (m_texture[0]) { delete m_texture[0]; }
	if (m_texture[1]) { delete m_texture[1]; }
}
