#include "FPSCameraScript.h"
#include "GameObject.h"
#include "inputclass.h"


FPSCameraScript::FPSCameraScript()
{
	m_Enable = true;
	m_RotateSpeed = 1.1f;
}

FPSCameraScript::FPSCameraScript(BaseGameObject* gameObject)
	: BaseScript(gameObject)
{
}

FPSCameraScript::~FPSCameraScript()
{
}


void FPSCameraScript::Start()
{
	m_GameObject->GetTransform()->TranslateAt(XMFLOAT3(0, 0, -5.0f));
}

void FPSCameraScript::Update()
{
	if (m_Enable) { handleInput(); }
}

void FPSCameraScript::handleInput()
{
	if (InputManager::IsKeyPressed(DIK_W))
	{
		m_GameObject->GetTransform()->MoveByLocal(XMFLOAT3(0, 0, 0.1f));
	}

	if (InputManager::IsKeyPressed(DIK_S))
	{
		m_GameObject->GetTransform()->MoveByLocal(XMFLOAT3(0, 0, -0.1f));
	}

	if (InputManager::IsKeyPressed(DIK_A))
	{
		m_GameObject->GetTransform()->MoveByLocal(XMFLOAT3(-0.1f, 0, 0));
	}

	if (InputManager::IsKeyPressed(DIK_D))
	{
		m_GameObject->GetTransform()->MoveByLocal(XMFLOAT3(0.1f, 0, 0));
	}

	if (InputManager::IsMouseAxisPressed())
	{
		m_GameObject->GetTransform()->Rotate(XMFLOAT3(InputManager::mouseIY * m_RotateSpeed,
													  InputManager::mouseIX * m_RotateSpeed,
													  0));
	}
}
