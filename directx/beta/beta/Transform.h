#pragma once
#include "Component.h"
#include <DirectXMath.h>

#define WorldForward XMVectorSet(0, 0, 1.0, 0)
#define WorldBackward XMVectorSet(0, 0, -1.0, 0)
#define WorldRight XMVectorSet(1.0, 0, 0, 0)
#define WorldLeft XMVectorSet(-1.0, 0, 0, 0)

using namespace DirectX;

class Transform : public BaseComponent
{
public:
	Transform(BaseGameObject*);
	Transform(const Transform&);

public:
	void Start() override;
	void Update() override;

public:
	// Move based on world unit vector.
	void MoveByWorld(XMFLOAT3);
	// Move based on object forward vector.
	void MoveByLocal(XMFLOAT3);
	void TranslateAt(XMFLOAT3);
	void Rotate(XMFLOAT3);
	void RotateAt(XMFLOAT3);
	void Resize(XMFLOAT3);

public:
	XMVECTOR ConvertFloat3ToVector(XMFLOAT3);
	XMFLOAT3 ConvertVectorToFloat3(XMVECTOR);
	XMMATRIX GetWorldMatrix();
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();
	XMFLOAT3 GetScale();

private:
	void update();

private:
	XMMATRIX m_World;
	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;
};

