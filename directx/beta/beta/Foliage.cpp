#include "Foliage.h"

Foliage::Foliage(D3DClass* directX3D, HWND hwnd)
	: BaseGameObject(directX3D, hwnd)
{
	m_Tag = "Foliage";
	m_Layer = LayerType::Base;
}

Foliage::Foliage(const Foliage& other)
	: BaseGameObject(other.m_DirectX3D, other.m_HWND)
{
}

Foliage::~Foliage()
{
}

void Foliage::Start()
{
	BaseGameObject::Start();
}

void Foliage::Update()
{
	BaseGameObject::Update();
}
