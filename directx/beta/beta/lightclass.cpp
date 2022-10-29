////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "lightclass.h"
#include "cameraclass.h"

Light::Light(D3DClass* directX3D, HWND hwnd)
	: BaseGameObject(directX3D, hwnd)
{
	m_Tag = "Light";
}


Light::Light(const Light& other)
	: BaseGameObject(other.m_DirectX3D, other.m_HWND)
{
}


Light::~Light()
{
}

void Light::Start()
{
	BaseGameObject::Start();

	SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetDirection(1.0f, 0.0f, 1.0f);
	SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	SetSpecularPower(32.0f);
}

void Light::Update()
{
	BaseGameObject::Update();
}

void Light::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void Light::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void Light::SetDirection(float x, float y, float z)
{
	m_direction = XMFLOAT3(x, y, z);
	return;
}

void Light::SetSpecularColor(float red, float green, float blue, float alpha)
{
	m_specularColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void Light::SetSpecularPower(float power)
{
	m_specularPower = power;
	return;
}

XMFLOAT4 Light::GetAmbientColor()
{
	return m_ambientColor;
}

XMFLOAT4 Light::GetDiffuseColor()
{
	return m_diffuseColor;
}

XMFLOAT3 Light::GetDirection()
{
	return m_direction;
}

XMFLOAT4 Light::GetSpecularColor()
{
	return m_specularColor;
}

float Light::GetSpecularPower()
{
	return m_specularPower;
}