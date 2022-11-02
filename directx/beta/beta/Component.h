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
	Bitmap
};
	
class BaseComponent
{
public:
	friend class BaseScript;

	BaseComponent();
	BaseComponent(BaseGameObject*);
	virtual ~BaseComponent();

public:
	virtual void Start() = 0;
	virtual void Update() = 0;

public:
	void AttachGameObject(BaseGameObject*);
	string GetName();
	bool IsEnable();

protected:
	vector<BaseComponent*> GetComponentList();
	vector<BaseScript*> GetScriptList();
	vector<BaseShader*> GetShaderList();

protected:
	string m_Name;
	bool m_Active;
	BaseGameObject* m_GameObject;
};

