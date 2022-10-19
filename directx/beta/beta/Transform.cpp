#include "Transform.h"

Transform::Transform(BaseGameObject* gameObject)
	: BaseComponent(gameObject)
{
	m_Name = "Transform";
	m_Active = true;

	m_World = XMMatrixIdentity();
	m_Position = XMFLOAT3(0, 0, 0);
	m_Rotation = XMFLOAT3(0, 0, 0);
	m_Scale = XMFLOAT3(1, 1, 1);
}

Transform::Transform(const Transform&)
{
}

void Transform::Update()
{
}

void Transform::Move(XMFLOAT3 position)
{
	m_Position.x += position.x;
	m_Position.y += position.y;
	m_Position.z += position.z;
}

void Transform::Rotate(XMFLOAT3 angle)
{
	m_Rotation.x += angle.x;
	m_Rotation.y += angle.y;
	m_Rotation.z += angle.z;
}

void Transform::TranslateAt(XMFLOAT3 position)
{
	m_Position.x = position.x;
	m_Position.y = position.y;
	m_Position.z = position.z;
}

void Transform::RotateAt(XMFLOAT3 angle)
{
	m_Rotation.x = angle.x;
	m_Rotation.y = angle.y;
	m_Rotation.z = angle.z;
}

void Transform::Resize(XMFLOAT3 scale)
{
	m_Scale.x = scale.x;
	m_Scale.y = scale.y;
	m_Scale.z = scale.z;
}

void Transform::Transpose(XMFLOAT3 position = XMFLOAT3(0.0f, 0.0f, 0.0f),
						  XMFLOAT3 rotation = XMFLOAT3(0.0f, 0.0f, 0.0f),
						  XMFLOAT3 scale = XMFLOAT3(0.0f, 0.0f, 0.0f))
{
	XMMATRIX movement = XMMatrixTranslation(position.x, position.y, position.z);
	XMMATRIX angle = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	XMMATRIX size = XMMatrixScaling(scale.x, scale.y, scale.z);


	m_World = size * angle * movement;
}

XMMATRIX Transform::GetWorldMatrix()
{
	return m_World;
}

XMFLOAT3 Transform::GetPosition()
{
	return m_Position;
}

XMFLOAT3 Transform::GetRotation()
{
	return m_Rotation;
}

XMFLOAT3 Transform::GetScale()
{
	return m_Scale;
}
