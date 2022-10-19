#include "Transform.h"

Transform::Transform(BaseGameObject* gameObject)
	: BaseComponent(gameObject)
{
	m_Name = "Transform";
	m_Active = true;

	m_World = XMMatrixIdentity();
	m_Position = XMFLOAT3(0, 0, 0);
	m_Rotation = XMFLOAT3(0, 0, 0);
	m_Scale = XMFLOAT3(0, 0, 0);
}

Transform::Transform(const Transform&)
{
}

void Transform::Initialize()
{
}

void Transform::Update()
{
}

void Transform::TranslateAt(XMFLOAT3 position)
{
	XMMATRIX temp;
	temp = XMMatrixTranslation(position.x, position.y, position.z);

	m_World += temp;
	m_Position.x += position.x;
	m_Position.y += position.y;
	m_Position.z += position.z;
}

void Transform::RotateAt(XMFLOAT3 rotation)
{
	XMMATRIX temp;
	temp = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

	m_World += temp;
	m_Rotation.x += rotation.x;
	m_Rotation.y += rotation.y;
	m_Rotation.z += rotation.z;
}

void Transform::Resize(XMFLOAT3 size)
{
	XMMATRIX temp;
	temp = XMMatrixScaling(size.x, size.y, size.z);

}

const XMMATRIX Transform::GetWorldMatrix()
{
	return m_World;
}

const XMFLOAT3 Transform::GetPosition()
{
	return m_Position;
}

const XMFLOAT3 Transform::GetRotation()
{
	return m_Rotation;
}

const XMFLOAT3 Transform::GetScale()
{
	return m_Scale;
}
