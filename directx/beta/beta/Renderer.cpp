#include "Renderer.h"

#include "GameObject.h"
#include "modelclass.h"
#include "Script.h"
#include "Transform.h"
#include "cameraclass.h"

Renderer::Renderer(BaseGameObject* gameObject)
	: BaseComponent(gameObject)
{
	m_Name = "Renderer";
	m_Active = true;
}

Renderer::~Renderer()
{
}

void Renderer::Start()
{
}

void Renderer::Update()
{
	
}

void Renderer::Render(vector<BaseGameObject*> gameObjectList, Camera* camera)
{
	renderMesh();
	renderShader(gameObjectList, camera);
}

void Renderer::renderMesh()
{
	for (auto component : GetComponentList())
	{
		Mesh* mesh;
		mesh = dynamic_cast<Mesh*>(component);

		if (mesh) { mesh->Render(m_GameObject->GetDirectX3D()->GetDeviceContext()); }
	}
}

void Renderer::renderShader(vector<BaseGameObject*> gameObjectList, Camera* camera)
{
	for (auto shader : GetShaderList())
	{
		shader->Render(gameObjectList, camera);
	}
}
