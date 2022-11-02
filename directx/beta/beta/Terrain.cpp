#include "Terrain.h"

Terrain::Terrain(D3DClass* directX3D, HWND hwnd)
	: BaseGameObject(directX3D, hwnd)
{
	m_Tag = "Terrain";
	m_Layer = LayerType::Base;

	m_width = 100;
	m_height = 100;
}

Terrain::Terrain(const Terrain& other)
	: BaseGameObject(other.m_DirectX3D, other.m_HWND)
{
}

Terrain::~Terrain()
{
}

void Terrain::Start()
{
	BaseGameObject::Start();
}

void Terrain::Update()
{
	BaseGameObject::Update();
}

Terrain* Terrain::SetWidthAndHeight(int width, int height)
{	
	m_width = width;
	m_height = height;

	return this;
}
