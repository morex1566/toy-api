#include "Shader.h"
#include "GameObject.h"
#include "cameraclass.h"

BaseShader::BaseShader()
{
}

BaseShader::BaseShader(BaseGameObject* gameObject)
{
	m_GameObject = gameObject;
}

BaseShader::~BaseShader()
{

}

bool BaseShader::Render(vector<BaseGameObject*> gameObjectList, Camera* camera)
{
	return true;
}

void BaseShader::AttachGameObject(BaseGameObject* gameObject)
{
	m_GameObject = gameObject;
}

string BaseShader::GetName()
{
	return m_Name;
}
