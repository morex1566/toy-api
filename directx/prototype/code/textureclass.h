#pragma once

#include <d3d11.h>
#include "GameObject.h"

class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D11Device*, const WCHAR*, GameObject*);
	void Shutdown();
};