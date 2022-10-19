#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>

#include "Script.h"

using namespace DirectX;

enum class ShaderType
{
	ColorShader,
	LightShader,
	TextureShader,
};

class BaseShader
{
public:
	BaseShader();
	virtual ~BaseShader();

public:
	virtual void Initialize();
	virtual bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*) = 0;

public:
	string GetName();

protected:
	string m_Name;
};

