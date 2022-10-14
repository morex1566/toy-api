#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <fstream>

#include "textureclass.h"
#include "GameObject.h"

using namespace DirectX;

class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};
	struct FaceType
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	};
	struct ObjectCount
	{
		int vertexCount;
		int indexCount;
		int textureCount;
		int faceCount;
	};

public:

	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, const WCHAR*, const WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	bool LoadModel(const WCHAR*);
	void ReleaseModel();

	vector<GameObject*> GetGameObjectList();
private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, const WCHAR*);
	void ReleaseTexture();

	bool ReadFileCounts(const WCHAR*);
	bool LoadDataStructures(const WCHAR*, int, int, int, int);

private:
	vector<GameObject*>			   gameObjectList;
	TextureClass*				   m_TextureManager;
	ID3D11Buffer*				   m_vertexBuffer;
	ID3D11Buffer*				   m_indexBuffer;
	ObjectCount					   counter;
};