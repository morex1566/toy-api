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
	SkydomeShader,
	SkyplaneShader,
	TerrainShader,
	FontShader
};

class BaseShader
{
public:
	BaseShader();
	BaseShader(BaseGameObject*);
	virtual ~BaseShader();

public:
	virtual bool Render(vector<BaseGameObject*>, Camera*);

public:
	void AttachGameObject(BaseGameObject*);
	string GetName();
	

protected:
	string m_Name;
	BaseGameObject* m_GameObject;
};

