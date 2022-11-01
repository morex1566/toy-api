////////////////////////////////////////////////////////////////////////////////
// Filename: skydomeshaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SKYDOMESHADERCLASS_H_
#define _SKYDOMESHADERCLASS_H_


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
// Class name: SkyDomeShaderClass
////////////////////////////////////////////////////////////////////////////////
class SkyDomeShaderClass : public BaseShader
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct GradientBufferType
	{
		XMVECTOR apexColor;
		XMVECTOR centerColor;
	};

public:
	SkyDomeShaderClass(BaseGameObject*, string, string);
	SkyDomeShaderClass(const SkyDomeShaderClass&);
	~SkyDomeShaderClass() override;

	bool Initialize();
	void Shutdown();
	bool Render(vector<BaseGameObject*>, Camera*) override;

public:
	void SetApexColor(XMVECTOR);
	void SetCenterColor(XMVECTOR);

private:
	bool InitializeShader(ID3D11Device*, HWND, const WCHAR*, const WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, const WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, XMVECTOR, XMVECTOR);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_gradientBuffer;

	string m_VSRoute;
	string m_PSRoute;

	XMVECTOR m_apexColor;
	XMVECTOR m_centerColor;
};

#endif