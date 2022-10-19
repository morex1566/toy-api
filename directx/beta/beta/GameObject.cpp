#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"
#include "modelclass.h"	
#include "Collider.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"

BaseGameObject::BaseGameObject(D3DClass* directX3D)
{
	m_DirectX3D = directX3D;

	AddComponent(ComponentType::Transform);
	AddComponent(ComponentType::Renderer);
}

BaseGameObject::BaseGameObject(const BaseGameObject&)
{
}

BaseGameObject::~BaseGameObject()
{
	clearList(m_ShaderList);
	clearList(m_ScriptList);
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

BaseGameObject* BaseGameObject::AddComponent(ComponentType type, string route = "")
{
	switch (type)
	{
	case ComponentType::Transform:
		m_ComponentList.push_back(new Transform(this));
		break;

	case ComponentType::Renderer:
		m_ComponentList.push_back(new Renderer(this));
		break;

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
}

BaseGameObject* BaseGameObject::AddShader(ShaderType type, string vsRoute = "", string psRoute = "")
{
	switch (type)
	{
	case ShaderType::ColorShader:
		m_ShaderList.push_back(new ColorShaderClass());
		break;

	case ShaderType::LightShader:
		m_ShaderList.push_back(new LightShaderClass());
		break;

	case ShaderType::TextureShader:
		m_ShaderList.push_back(new TextureShaderClass());
		break;

	default:
		break;
	}
	return this;
}

BaseGameObject* BaseGameObject::AddScript(BaseScript* script)
{
	m_ScriptList.push_back(script);

	return this;
}

void BaseGameObject::initializeComponentList()
{
	for (auto component : m_ComponentList)
	{
		component->Initialize();
	}
}

void BaseGameObject::initializeShaderList()
{
	for (auto shader : m_ShaderList)
	{
		shader->Initialize();
	}
}

void BaseGameObject::initializeScriptList()
{
	for (auto script : m_ScriptList)
	{
		script->Initialize();
	}
}

void BaseGameObject::Initialize()
{
}

void BaseGameObject::Update()
{
}

void BaseGameObject::Render()
{
}

template<typename T>
inline void BaseGameObject::clearList(vector<T*> list)
{
	for (auto element : list) { delete element; }

	list.clear();
	vector<T*>().swap(list);
}
