////////////////////////////////////////////////////////////////////////////////
// Filename: skyplaneshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SKYPLANESHADERCLASS_H_
#define _SKYPLANESHADERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <fstream>

#include "Shader.h"

using namespace std;
using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: SkyPlaneShaderClass
////////////////////////////////////////////////////////////////////////////////
class SkyPlaneShaderClass : public BaseShader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct SkyBufferType
	{
		float firstTranslationX;
		float firstTranslationZ;
		float secondTranslationX;
		float secondTranslationZ;
		float brightness;
		XMVECTOR padding;
	};

public:
	SkyPlaneShaderClass(BaseGameObject*, string, string);
	SkyPlaneShaderClass(const SkyPlaneShaderClass&);
	~SkyPlaneShaderClass() override;

	bool Initialize();
	void Shutdown();
	bool Render(vector<BaseGameObject*>, Camera*) override;

private:
	bool InitializeShader(ID3D11Device*, HWND, const WCHAR*, const WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, const WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, float, float,
							 float, float, float);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_skyBuffer;

	string m_VSRoute;
	string m_PSRoute;
};

#endif