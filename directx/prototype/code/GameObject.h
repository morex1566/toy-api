#pragma once

#include <d3d11.h>

#include "Component.h"
#include "UniversalType.h"

class GameObject
{
public:
	GameObject();
	GameObject(const GameObject&);
	~GameObject();

	/* Utility */

	const Component* FindComponentWithName(string);

	ModelType* GetModel();
	ID3D11ShaderResourceView* GetTexture();

	void SetModel(ModelType*);
	void SetTexture(ID3D11ShaderResourceView*);
private:
	vector<Component*> componentList;
	ModelType* model;
	ID3D11ShaderResourceView* texture;
};

