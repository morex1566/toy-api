////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTURECLASS_H_
#define _TEXTURECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include "Component.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: TextureClass
////////////////////////////////////////////////////////////////////////////////
class Texture : public BaseComponent
{
public:
	Texture(BaseGameObject*, string);
	Texture(const Texture&);
	~Texture() override;

	bool Initialize();
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

public:
	void Start() override;
	void Update() override;

private:
	string m_Route;
	ID3D11ShaderResourceView* m_texture;
};

#endif