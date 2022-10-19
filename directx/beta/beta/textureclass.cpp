////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "textureclass.h"
#include "DDSTextureLoader.h"

using namespace DirectX;

Texture::Texture(BaseGameObject* gameObject)
	: BaseComponent(gameObject)
{
	m_texture = 0;
}


Texture::Texture(const Texture& other)
{
}


Texture::~Texture()
{
}


bool Texture::Initialize(ID3D11Device* device, const WCHAR* filename)
{
	HRESULT result;

	// Load texture data from a file by using DDS texture loader.
	result = CreateDDSTextureFromFile(device, filename, nullptr, &m_texture);
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