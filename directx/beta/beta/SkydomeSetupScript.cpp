#include "SkydomeSetupScript.h"
#include "GameObject.h"
#include "skydomeshaderclass.h"
#include "cameraclass.h"

SkydomeSetupScript::SkydomeSetupScript()
{
    m_apexColor = XMVectorSet(0, 0, 0, 1);
    m_centerColor = XMVectorSet(0, 0, 0, 1);
}

SkydomeSetupScript::SkydomeSetupScript(Camera* camera)
{
    m_apexColor = XMVectorSet(0, 0, 0, 1);
    m_centerColor = XMVectorSet(0, 0, 0, 1);
    m_mainCamera = camera;
}

SkydomeSetupScript::SkydomeSetupScript(BaseGameObject* gameObject)
    : BaseScript(gameObject)
{
}

SkydomeSetupScript::~SkydomeSetupScript()
{
}

void SkydomeSetupScript::Start()
{
    m_apexColor = XMVectorSet(0, 0.15f, 0.66f, 1.0f);
    m_centerColor = XMVectorSet(0.81f, 0.38f, 0.66f, 1.0f);

    XMFLOAT3 cameraPosition = m_mainCamera->GetTransform()->GetPosition();
    m_GameObject->GetTransform()->TranslateAt(cameraPosition);

    // Set skydome color if shader is exist.
    SkyDomeShaderClass* shader =
        dynamic_cast<SkyDomeShaderClass*>(m_GameObject->FindShaderWithName("SkydomeShader"));

    if (shader)
    {
        shader->SetApexColor(m_apexColor);
        shader->SetCenterColor(m_centerColor);
    }
}

void SkydomeSetupScript::Update()
{
    if (m_mainCamera)
    {
        XMFLOAT3 cameraPosition = m_mainCamera->GetTransform()->GetPosition();

        m_GameObject->GetTransform()->TranslateAt(cameraPosition);
    }
}

XMVECTOR SkydomeSetupScript::GetApexColor()
{
    return m_apexColor;
}

XMVECTOR SkydomeSetupScript::GetCenterColor()
{
    return m_centerColor;
}

void SkydomeSetupScript::SetApexColor(XMVECTOR color)
{
    m_apexColor = color;
}

void SkydomeSetupScript::SetCenterColor(XMVECTOR color)
{
    m_centerColor = color;
}
