#include "Cloud.h"

Cloud::Cloud(D3DClass* directX3D, HWND hwnd)
	: BaseGameObject(directX3D, hwnd)
{
	m_Tag = "Object";
	m_Layer = LayerType::Blend;
}

Cloud::Cloud(const Cloud& other)
	: BaseGameObject(other.m_DirectX3D, other.m_HWND)
{
}

Cloud::~Cloud()
{
}

void Cloud::Start()
{
	BaseGameObject::Start();
}

void Cloud::Update()
{
	BaseGameObject::Update();
}
