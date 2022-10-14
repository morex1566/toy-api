////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "textureclass.h"
#include "DDSTextureLoader.h"

using namespace DirectX;

TextureClass::TextureClass()
{
}
TextureClass::TextureClass(const TextureClass& other)
{
}
TextureClass::~TextureClass()
{
}


bool TextureClass::Initialize(ID3D11Device* device, const WCHAR* filename, GameObject* gameObject)
{
	HRESULT result;
	ID3D11ShaderResourceView* texture;

	// Load texture data from a file by using DDS texture loader.
	result = CreateDDSTextureFromFile(device, filename, nullptr, &texture);
	if (FAILED(result))
	{
		return false;
	}

	gameObject->SetTexture(texture);

	return true;
}


void TextureClass::Shutdown()
{
	return;
}