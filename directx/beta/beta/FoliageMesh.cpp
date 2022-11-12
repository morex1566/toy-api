#include "FoliageMesh.h"

FoliageMesh::FoliageMesh(BaseGameObject*, string)
{
}

FoliageMesh::FoliageMesh(const FoliageMesh&)
{
}

FoliageMesh::~FoliageMesh()
{
}

bool FoliageMesh::Initialize()
{
	return false;
}

void FoliageMesh::Shutdown()
{
}

void FoliageMesh::Render(ID3D11DeviceContext*)
{
}

bool FoliageMesh::Frame(XMFLOAT3, ID3D11DeviceContext*)
{
	return false;
}

int FoliageMesh::GetVertexCount()
{
	return 0;
}

int FoliageMesh::GetInstanceCount()
{
	return 0;
}

ID3D11ShaderResourceView* FoliageMesh::GetTexture()
{
	return nullptr;
}

void FoliageMesh::Start()
{
}

void FoliageMesh::Update()
{
}

bool FoliageMesh::InitializeBuffers(ID3D11Device*)
{
	return false;
}

void FoliageMesh::ShutdownBuffers()
{
}

void FoliageMesh::RenderBuffers(ID3D11DeviceContext*)
{
}

bool FoliageMesh::LoadTexture(ID3D11Device*, WCHAR*)
{
	return false;
}

void FoliageMesh::ReleaseTexture()
{
}

bool FoliageMesh::GeneratePositions()
{
	return false;
}
