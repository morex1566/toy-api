#include "Skydome.h"

Skydome::Skydome(D3DClass* directX3D, HWND hwnd)
	: BaseGameObject(directX3D, hwnd)
{
	m_Tag = "Skydome";
	m_Layer = LayerType::BackGround;
}

Skydome::Skydome(const Skydome& other)
	: BaseGameObject(other.m_DirectX3D, other.m_HWND)
{
}

Skydome::~Skydome()
{
}

void Skydome::Start()
{
	BaseGameObject::Start();
}

void Skydome::Update()
{
	BaseGameObject::Update();
}
