#pragma once

#include <d3d11.h>

#include "modelclass.h"
#include "textureclass.h"
#include "Component.h"
#include "UniversalType.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	const shared_ptr<Component> FindComponentWithName(string);
	const shared_ptr<ModelType> GetModel();
	const shared_ptr<ID3D11ShaderResourceView> GetTexture();

private:
	vector<shared_ptr<Component>> componentList;
	std::shared_ptr<ModelType> model;
	std::shared_ptr<ID3D11ShaderResourceView> texture;
};

