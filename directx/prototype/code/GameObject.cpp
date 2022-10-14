#include "GameObject.h"

GameObject::GameObject()
{

}
GameObject::GameObject(const GameObject& other)
{
}
GameObject::~GameObject()
{
	DestroyVector<Component*>(componentList);
	
	if (!model) { delete model; }
	if (!texture) { delete texture; }
}

const Component* GameObject::FindComponentWithName(string name)
{
	for (auto component : componentList)
	{
		if (component->name == name) { return component; }
	}

	return nullptr;
}

ModelType* GameObject::GetModel()
{
	return model;
}
ID3D11ShaderResourceView* GameObject::GetTexture()
{
	return texture;
}

void GameObject::SetModel(ModelType* model_)
{
	model = model_;
}
void GameObject::SetTexture(ID3D11ShaderResourceView* texture_)
{
	texture = texture_;
}
