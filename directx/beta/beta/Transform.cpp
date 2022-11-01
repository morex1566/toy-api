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

void Transform::Start()
{
}

void Transform::Update()
{

}

void Transform::MoveByWorld(XMFLOAT3 position)
{
	m_Position.x += position.x;
	m_Position.y += position.y;
	m_Position.z += position.z;

	update();
}

void Transform::MoveByLocal(XMFLOAT3 position)
{
	XMMATRIX rotationYTempMatrix = XMMatrixRotationY(m_Rotation.y);
	XMVECTOR right = XMVector3TransformCoord(WorldRight, rotationYTempMatrix);
	XMVECTOR forward = XMVector3TransformCoord(WorldForward, rotationYTempMatrix);

	m_Position.x += ConvertVectorToFloat3(right * position.x).x + ConvertVectorToFloat3(forward * position.z).x;
	m_Position.y += ConvertVectorToFloat3(right * position.x).y + ConvertVectorToFloat3(forward * position.z).y;
	m_Position.z += ConvertVectorToFloat3(right * position.x).z + ConvertVectorToFloat3(forward * position.z).z;

	update();
}

void Transform::Rotate(XMFLOAT3 angle)
{
	m_Rotation.x += angle.x;
	m_Rotation.y += angle.y;
	m_Rotation.z += angle.z;

	update();
}

void Transform::TranslateAt(XMFLOAT3 position)
{
	m_Position.x = position.x;
	m_Position.y = position.y;
	m_Position.z = position.z;

	update();
}

void Transform::RotateAt(XMFLOAT3 angle)
{
	m_Rotation.x = angle.x;
	m_Rotation.y = angle.y;
	m_Rotation.z = angle.z;

	update();
}

void Transform::Resize(XMFLOAT3 scale)
{
	m_Scale.x = scale.x;
	m_Scale.y = scale.y;
	m_Scale.z = scale.z;

	update();
}

XMMATRIX Transform::GetWorldMatrix()
{
	return m_World;
}

XMVECTOR Transform::ConvertFloat3ToVector(XMFLOAT3 float3)
{
	XMFLOAT3* temp = new XMFLOAT3(float3.x, float3.y, float3.z);
	XMVECTOR result = XMLoadFloat3(temp);

	delete temp;
	return result;
}

XMFLOAT3 Transform::ConvertVectorToFloat3(XMVECTOR vector)
{
	XMFLOAT3* temp = new XMFLOAT3();
	XMFLOAT3 result;
	XMStoreFloat3(temp, vector);

	result = *temp;

	delete temp;
	return result;
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

void Transform::SetWorldMatrix(XMMATRIX matrix)
{
	m_World = matrix;
}

void Transform::update()
{
	XMMATRIX movement = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX angle = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	XMMATRIX size = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);

	m_World = size * angle * movement;
}
