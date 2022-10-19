#pragma once
#include <string>
#include <vector>

using namespace std;

class BaseGameObject;
class BaseScript;
class BaseShader;
class D3DClass;

enum class ComponentType
{
	Transform,
	Renderer,
	Mesh,
	Collider,
	Texture,
};
	
class BaseComponent
{
public:
	friend class BaseScript;

	BaseComponent();
	BaseComponent(BaseGameObject*);
	virtual ~BaseComponent();

public:
	virtual void Initialize();
	virtual void Update();

public:
	string GetName();
	bool IsEnable();

protected:
	D3DClass* GetDirectX3D();
	vector<BaseComponent*> GetComponentList();
	vector<BaseScript*> GetScriptList();
	vector<BaseShader*> GetShaderList();

protected:
	string m_Name;
	bool m_Active;
	BaseGameObject* m_GameObject;
};

