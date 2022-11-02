#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <string>
#include <fstream>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "Component.h"
#include "textureclass.h"

using namespace std;
using namespace DirectX;

const int TEXTURE_REPEAT = 32;


class Bitmap : public BaseComponent
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct HeightMapType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VectorType
	{
		float x, y, z;
	};

public:
	Bitmap(BaseGameObject*, string, string, string, string);
	Bitmap(string, string, string, string);
	Bitmap(BaseGameObject*);
	Bitmap(const Bitmap&);
	~Bitmap() override;

	bool Initialize();
	void Shutdown();
	void Render();

	int GetIndexCount();

	ID3D11ShaderResourceView* GetGrassTexture();
	ID3D11ShaderResourceView* GetSlopeTexture();
	ID3D11ShaderResourceView* GetRockTexture();

public:
	void Start() override;
	void Update() override;

private:
	bool LoadHeightMap();
	void NormalizeHeightMap();
	bool CalculateNormals();
	void ShutdownHeightMap();

	void CalculateTextureCoordinates();

	bool LoadTextures();

	bool InitializeBuffers();
	void ShutdownBuffers();
	void RenderBuffers();

private:
	int m_terrainWidth, m_terrainHeight;
	int m_vertexCount, m_indexCount;
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	HeightMapType* m_heightMap;
	ID3D11ShaderResourceView* m_GrassTexture, * m_SlopeTexture, * m_RockTexture;
	
	string m_bitmapRoute, m_grassTextureRoute, m_slopeTextureRoute, m_rockTextureRoute;
};

