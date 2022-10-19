#pragma once
#include "Component.h"
#include <DirectXMath.h>

using namespace DirectX;

class Transform : public BaseComponent
{
public:
	Transform(BaseGameObject*);
	Transform(const Transform&);

public:
	void Update() override;

public:
	void TranslateAt(XMFLOAT3);
	void RotateAt(XMFLOAT3);
	void Resize(XMFLOAT3);
	void Transpose(XMFLOAT3, XMFLOAT3, XMFLOAT3);

public:
	const XMMATRIX GetWorldMatrix();
	const XMFLOAT3 GetPosition();
	const XMFLOAT3 GetRotation();
	const XMFLOAT3 GetScale();

	XMFLOAT3 operator=(XMFLOAT3& ref)
	{
		return XMFLOAT3(ref.x, ref.y, ref.z);
	}

private:
	XMMATRIX m_World;
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;
};

