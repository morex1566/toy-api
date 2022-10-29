#include "Object.h"
#include "GameObject.h"

Object::Object(D3DClass* directX3D, HWND hwnd)
	: BaseGameObject(directX3D, hwnd)
{
	m_Tag = "Object";
}

Object::Object(const Object& other)
	: BaseGameObject(other.m_DirectX3D, other.m_HWND)
{
}

Object::~Object()
{
}

void Object::Start()
{
	BaseGameObject::Start();
}

void Object::Update()
{
	BaseGameObject::Update();
}
