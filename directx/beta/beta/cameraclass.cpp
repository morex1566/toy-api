////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"
#include "graphicsclass.h"
#include "inputclass.h"

Camera::Camera(D3DClass* directX3D, HWND hwnd, Scene* scene)
	: BaseGameObject(directX3D, hwnd), m_CurrentScene(scene)
{
	m_Tag = "Camera";
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

	m_Transform->TranslateAt(XMFLOAT3(0, 0, -5.0f));
}

void Camera::Update()
{
	BaseGameObject::Update();

	if (InputManager::IsKeyPressed(DIK_W))
	{
		m_Transform->Move(XMFLOAT3(0, 0, 0.1f));
	}

	if (InputManager::IsKeyPressed(DIK_S))
	{
		m_Transform->Move(XMFLOAT3(0, 0, -0.1f));
	}

	if (InputManager::IsKeyPressed(DIK_A))
	{
		m_Transform->Move(XMFLOAT3(-0.1f, 0, 0));
	}

	if (InputManager::IsKeyPressed(DIK_D))
	{
		m_Transform->Move(XMFLOAT3(0.1f, 0, 0));
	}


	GetTransform()->Transpose(GetTransform()->GetPosition(),
							  GetTransform()->GetRotation(),
							  GetTransform()->GetScale());
}

// This uses the position and rotation of the camera to build and to update the view matrix.
void Camera::Render(vector<BaseGameObject*> gameObjectList, Camera* camera)
{
	BaseGameObject::Render(gameObjectList, camera);

	XMVECTOR up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

	XMFLOAT3* temp = new XMFLOAT3;
	temp->x = m_Transform->GetPosition().x;
	temp->y = m_Transform->GetPosition().y;
	temp->z = m_Transform->GetPosition().z;


	// Setup the vector that points upwards.
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Setup the position of the camera in the world.
	position = XMLoadFloat3(temp);

	// Setup where the camera is looking by default.
	lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_Transform->GetRotation().x * 0.0174532925f;
	yaw   = m_Transform->GetRotation().y * 0.0174532925f;
	roll  = m_Transform->GetRotation().z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);

	delete temp;

	return;
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
