#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <string>

using namespace DirectX;
using namespace std;

class Camera;
class BaseGameObject;

enum class ShaderType
{
	ColorShader,
	LightShader,
	TextureShader,
};

class BaseShader
{
public:
	BaseShader(BaseGameObject*);
	virtual ~BaseShader();

public:
	virtual bool Render(vector<BaseGameObject*>, Camera*);

public:
	string GetName();
	

protected:
	string m_Name;
	BaseGameObject* m_GameObject;
};

