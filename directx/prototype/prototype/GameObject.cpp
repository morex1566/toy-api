#include "GameObject.h"

GameObject::GameObject()
{

}
GameObject::~GameObject()
{
	componentList.clear();
}

// Get readonly component with name
const shared_ptr<Component> GameObject::FindComponentWithName(string name)
{
	for (auto component : componentList)
	{
		if (component->name == name) { return component; }
	}

	return nullptr;
}


// Get readonly model
const shared_ptr<ModelType> GameObject::GetModel()
{
	return model;
}
// Get readonly texture
const shared_ptr<ID3D11ShaderResourceView> GameObject::GetTexture()
{
	return texture;
}