#pragma once

#include <vector>
#include <string>

#include "d3dclass.h"
#include "Component.h"
#include "Script.h"
#include "Shader.h"

#include "Transform.h"
#include "Renderer.h"

enum class LayerType
{
	Base,
	BackGround,
	Blend
};

enum class TagType
{

};


class BaseGameObject
{
public:
	friend class BaseComponent;
	friend class BaseShader;
	friend class BaseScript;

	BaseGameObject(D3DClass*, HWND);
	BaseGameObject(const BaseGameObject&);
	virtual ~BaseGameObject();
	

public:
	virtual void Start();
	virtual void Update();
	void Render(vector<BaseGameObject*>, Camera*);


public:
	string GetTag();
	LayerType GetLayer();
	void SetTag(string);
	void SetLayer(LayerType);
	BaseScript* FindScriptWithName(string);
	BaseShader* FindShaderWithName(string);
	BaseComponent* FindComponentWithName(string);

	BaseGameObject* AddComponent(ComponentType, string = "");
	BaseGameObject* AddComponent(BaseComponent*);
	BaseGameObject* AddShader(ShaderType, string = "", string = "");
	BaseGameObject* AddShader(BaseShader*);
	BaseGameObject* AddScript(BaseScript*);

	D3DClass* GetDirectX3D();
	HWND GetHWND();
	Transform* GetTransform();

private:
	template <typename T>
	void clearList(vector<T*>);

protected:
	Transform* m_Transform;
	Renderer* m_Renderer;
	string m_Tag;
	LayerType m_Layer;
	D3DClass* m_DirectX3D;
	HWND m_HWND;
	vector<BaseComponent*> m_ComponentList;
	vector<BaseShader*> m_ShaderList;
	vector<BaseScript*> m_ScriptList;

};