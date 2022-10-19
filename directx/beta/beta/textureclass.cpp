////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "textureclass.h"
#include "DDSTextureLoader.h"
#include "GameObject.h"	
#include "d3dclass.h"

using namespace DirectX;

Texture::Texture(BaseGameObject* gameObject, string route)
	: BaseComponent(gameObject), m_Route(route)
{
	bool result;

	m_Name = "Texture";

	m_texture = 0;

	result = Initialize();
	if (!result)
	{
		MessageBox(m_GameObject->GetHWND(), L"Could not initialize the texture.", L"Error", MB_OK);
		exit(0);
	}
}


Texture::Texture(const Texture& other)
	: BaseComponent(other.m_GameObject)
{
}


Texture::~Texture()
{
	Shutdown();
}


bool Texture::Initialize()
{
	HRESULT result;

	// Load texture data from a file by using DDS texture loader.
	result = CreateDDSTextureFromFile(m_GameObject->GetDirectX3D()->GetDevice(),
									  wstring(m_Route.begin(), m_Route.end()).c_str(),
									  nullptr,
									  &m_texture);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}


void Texture::Shutdown()
{
	// Release the texture resource.
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}


ID3D11ShaderResourceView* Texture::GetTexture()
{
	return m_texture;
}