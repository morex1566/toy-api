#include "Renderer.h"

#include "GameObject.h"
#include "modelclass.h"
#include "Script.h"
#include "textureshaderclass.h"
#include "Transform.h"

Renderer::Renderer(BaseGameObject* gameObject)
	: BaseComponent(gameObject)
{
	m_Name = "Renderer";
	m_Active = true;
}

Renderer::~Renderer()
{
}

void Renderer::Initialize()
{
}

void Renderer::Update()
{
	
}

void Renderer::Render()
{
	renderMesh();
}

void Renderer::renderMesh()
{
	Mesh* mesh;
	mesh = dynamic_cast<Mesh*>(m_GameObject->FindComponentWithName("Mesh"));

	if(mesh) { mesh->Render(GetDirectX3D()->GetDeviceContext()); }
}

void Renderer::renderShader()
{
	int indexCount;
	indexCount = dynamic_cast<Mesh*>(m_GameObject->FindComponentWithName("Mesh"))->GetIndexCount();

	Transform* transform;
	transform = dynamic_cast<Transform*>(m_GameObject->FindComponentWithName("Transform"));
	


	/*for (auto shader : GetShaderList())
	{
		if (shader->GetName() == "TextureShader")
		{
			dynamic_cast<TextureShaderClass*>(shader)->Render(GetDirectX3D()->GetDeviceContext(),
															  mesh->GetIndexCount(),
															  );
		}
	}*/
}
