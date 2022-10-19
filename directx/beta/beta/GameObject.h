#pragma once

#include <vector>

#include "d3dclass.h"
#include "Component.h"
#include "Script.h"
#include "Shader.h"

class BaseGameObject
{
public:
	friend class BaseComponent;
	friend class BaseShader;
	friend class BaseScript;

	BaseGameObject(D3DClass*);
	BaseGameObject(const BaseGameObject&);
	virtual ~BaseGameObject();
	

public:
	virtual void Initialize();
	virtual void Update();
	void Render();


public:
	BaseScript* FindScriptWithName(string);
	BaseShader* FindShaderWithName(string);
	BaseComponent* FindComponentWithName(string);
	BaseGameObject* AddComponent(ComponentType, string = "");
	BaseGameObject* AddShader(ShaderType, string = "", string = "");
	BaseGameObject* AddScript(BaseScript*);


private:
	template <typename T>
	void clearList(vector<T*>);

	void initializeComponentList();
	void initializeShaderList();
	void initializeScriptList();


protected:
	D3DClass* m_DirectX3D;
	vector<BaseComponent*> m_ComponentList;
	vector<BaseShader*> m_ShaderList;
	vector<BaseScript*> m_ScriptList;

};