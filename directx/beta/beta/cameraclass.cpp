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
	m_Layer = LayerType::Base;

	m_cameraTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	m_cameraUp = XMVectorSet(0, 1.0f, 0, 0);

	reflectionHeight = 0;
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

	updateStandardViewMatrix();
	updateReflectionViewMatrix();
}
		
void Camera::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}

XMMATRIX Camera::GetViewMatrix()
{
	return m_viewMatrix;
}

XMMATRIX Camera::GetReflectionViewMatrix()
{
	return m_reflectionViewMatrix;
}

void Camera::SetReflectionHeight(float height_)
{
	reflectionHeight = height_;
}

Camera* Camera::SetAsMainCamera()
{
	m_CurrentScene->m_MainCamera = this;

	return this;
}

void Camera::updateStandardViewMatrix()
{
	float pitch = m_Transform->GetRotation().x;
	float yaw = m_Transform->GetRotation().y;

	m_cameraRotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, 0);

	m_cameraTarget = XMVector3TransformCoord(WorldForward, m_cameraRotationMatrix);
	m_cameraTarget = XMVector3Normalize(m_cameraTarget);
	m_cameraTarget = m_cameraTarget + m_Transform->ConvertFloat3ToVector(m_Transform->GetPosition());

	m_cameraUp = XMVector3TransformCoord(m_cameraUp, XMMatrixRotationY(yaw));

	m_viewMatrix = XMMatrixLookAtLH(m_Transform->ConvertFloat3ToVector(m_Transform->GetPosition()), m_cameraTarget, m_cameraUp);
}

void Camera::updateReflectionViewMatrix()
{
	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.  Invert the X rotation for reflection.
	float pitch = -m_Transform->GetRotation().x;
	float yaw = m_Transform->GetRotation().y;
	float roll = m_Transform->GetRotation().z;
	

	// Create the rotation matrix from the yaw, pitch, and roll values.
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(yaw, pitch, roll);


	// Setup the position of the camera in the world.  For planar reflection invert the Y position of the camera.
	XMFLOAT3 position = m_Transform->GetPosition();
	position.y = -position.y + (reflectionHeight * 2.0f);


	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	// Translate the rotated camera position to the location of the viewer.
	XMVECTOR lookAt;
	lookAt = XMVector3TransformCoord(WorldForward, m_cameraRotationMatrix);
	lookAt = XMVector3Normalize(m_cameraTarget);
	lookAt = lookAt + m_Transform->ConvertFloat3ToVector(position);


	// Finally create the reflection view matrix from the three updated vectors.
	m_reflectionViewMatrix = XMMatrixLookAtLH(m_Transform->ConvertFloat3ToVector(position), m_cameraTarget, m_cameraUp);


	return;
}
