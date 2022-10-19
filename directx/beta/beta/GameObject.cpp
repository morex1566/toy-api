#include "GameObject.h"
#include "modelclass.h"	
#include "Collider.h"
#include "lightshaderclass.h"
#include "textureclass.h"

BaseGameObject::BaseGameObject(D3DClass* directX3D, HWND hwnd)
{
	m_DirectX3D = directX3D;
	m_HWND = hwnd;

	m_Transform = new Transform(this);
	m_Renderer = new Renderer(this);

	AddComponent(m_Transform);
	AddComponent(m_Renderer);
}

BaseGameObject::BaseGameObject(const BaseGameObject&)
{
}

BaseGameObject::~BaseGameObject()
{
	clearList(m_ShaderList);
	clearList(m_ScriptList);
}

string BaseGameObject::GetTag()
{
	return m_Tag;
}

BaseScript* BaseGameObject::FindScriptWithName(string name)
{
	for (auto script : m_ScriptList)
	{
		if (script->GetName() == name) { return script; }
	}

	return nullptr;
}

BaseShader* BaseGameObject::FindShaderWithName(string name)
{
	for (auto shader : m_ShaderList)
	{
		if (shader->GetName() == name) { return shader; }
	}
	return nullptr;
}

BaseComponent* BaseGameObject::FindComponentWithName(string name)
{
	for (auto component : m_ComponentList)
	{
		if (component->GetName() == name) { return component; }
	}
	return nullptr;
}

BaseGameObject* BaseGameObject::AddComponent(ComponentType type, string route)
{
	switch (type)
	{
	case ComponentType::Mesh:
		m_ComponentList.push_back(new Mesh(this, route));
		break;

	case ComponentType::Collider:
		m_ComponentList.push_back(new Collider(this));
		break;

	case ComponentType::Texture:
		m_ComponentList.push_back(new Texture(this, route));
		break;

	default:
		break;
	}

	return this;
}

BaseGameObject* BaseGameObject::AddComponent(BaseComponent* component)
{
	m_ComponentList.push_back(component);

	return this;
}

BaseGameObject* BaseGameObject::AddShader(ShaderType type, string vsRoute, string psRoute)
{
	switch (type)
	{
	case ShaderType::ColorShader:
		break;

	case ShaderType::LightShader:
		m_ShaderList.push_back(new LightShaderClass(this, vsRoute, psRoute));
		break;

	case ShaderType::TextureShader:
		break;

	default:
		break;
	}

	return this;
}

BaseGameObject* BaseGameObject::AddScript(BaseScript* script)
{
	BaseScript* temp = script;
	temp->AttachGameObject(this);

	m_ScriptList.push_back(temp);

	return this;
}

D3DClass* BaseGameObject::GetDirectX3D()
{
	return m_DirectX3D;
}

HWND BaseGameObject::GetHWND()
{
	return m_HWND;
}

Transform* BaseGameObject::GetTransform()
{
	return m_Transform;
}

void BaseGameObject::Start()
{
	for (auto script : m_ScriptList)
	{
		script->Start();
	}
}

void BaseGameObject::Update()
{
	for (auto script : m_ScriptList)
	{
		script->Update();
	}
}

void BaseGameObject::Render(vector<BaseGameObject*> gameObjectList, Camera* camera)
{
	dynamic_cast<Renderer*>(FindComponentWithName("Renderer"))->Render(gameObjectList, camera);
}

template<typename T>
inline void BaseGameObject::clearList(vector<T*> list)
{
	for (auto element : list) { delete element; }

	list.clear();
	vector<T*>().swap(list);
}
