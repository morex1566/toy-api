////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"
#include "graphicsclass.h"
#include "inputclass.h"
#include "Transform.h"


Camera::Camera(D3DClass* directX3D, HWND hwnd, Scene* scene)
	: BaseGameObject(directX3D, hwnd), m_CurrentScene(scene)
{
	m_Tag = "Camera";

	m_cameraTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_cameraUp = XMVectorSet(0, 1.0f, 0, 0);
}


Camera::Camera(const Camera& other)
	: BaseGameObject(other.m_DirectX3D, other.m_HWND)
{
}


Camera::~Camera()
{
}

void Camera::Start()
{
	BaseGameObject::Start();
}

void Camera::Update()
{
	BaseGameObject::Update();

	float pitch = m_Transform->GetRotation().x;
	float yaw = m_Transform->GetRotation().y;

	m_cameraRotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, 0);

	m_cameraTarget = XMVector3TransformCoord(WorldForward, m_cameraRotationMatrix);
	m_cameraTarget = XMVector3Normalize(m_cameraTarget);
	m_cameraTarget = m_cameraTarget + m_Transform->ConvertFloat3ToVector(m_Transform->GetPosition());
	
	m_cameraUp = XMVector3TransformCoord(m_cameraUp, XMMatrixRotationY(yaw));
	
	m_viewMatrix = XMMatrixLookAtLH(m_Transform->ConvertFloat3ToVector(m_Transform->GetPosition()), m_cameraTarget, m_cameraUp);
}
		
void Camera::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}

XMMATRIX Camera::GetViewMatrix()
{
	return m_viewMatrix;
}

Camera* Camera::SetAsMainCamera()
{
	m_CurrentScene->m_MainCamera = this;

	return this;
}
