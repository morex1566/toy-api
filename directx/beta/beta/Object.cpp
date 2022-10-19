#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "Renderer.h"
#include "modelclass.h"

Object::Object(D3DClass* directX3D)
	: BaseGameObject(directX3D)
{
}

Object::Object(const Object& other)
	: BaseGameObject(other.m_DirectX3D)
{
}

Object::~Object()
{
}

void Object::Update()
{
	updateComponent();
	updateScript();
}

void Object::updateComponent()
{
	for (auto component : m_ComponentList)
	{
		component->Update();
	}
}

void Object::updateScript()
{
	for (auto script : m_ScriptList)
	{
		script->Update();
	}
}
