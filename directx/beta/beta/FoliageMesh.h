#pragma once
#include <d3d11.h>
#include <directxmath.h>
#include <string>
#include <fstream>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "Component.h"


using namespace std;
using namespace DirectX;


class FoliageMesh : public BaseComponent
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

	struct FoliageType
	{
		float x, z;
		float r, g, b;
	};

	struct InstanceType
	{
		XMMATRIX matrix;
		XMFLOAT3 color;
	};

public:
	FoliageMesh(BaseGameObject*, string);
	FoliageMesh(const FoliageMesh&);
	~FoliageMesh() override;

	bool Initialize();
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	bool Frame(XMFLOAT3, ID3D11DeviceContext*);

	int GetVertexCount();
	int GetInstanceCount();

	ID3D11ShaderResourceView* GetTexture();

public:
	void Start() override;
	void Update() override;

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool GeneratePositions();

private:
	int m_foliageCount;
	FoliageType* m_foliageArray;
	InstanceType* m_Instances;
	ID3D11Buffer* m_vertexBuffer, * m_instanceBuffer;
	int m_vertexCount, m_instanceCount;
	ID3D11ShaderResourceView* m_Texture;
	float m_windRotation;
	int m_windDirection;

};

