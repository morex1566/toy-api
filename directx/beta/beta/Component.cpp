#include "Component.h"
#include "d3dclass.h"
#include "GameObject.h"
#include "Script.h" 
#include "Shader.h"

BaseComponent::BaseComponent()
{
}

BaseComponent::BaseComponent(BaseGameObject* gameObject)
{
    m_GameObject = gameObject;
}

BaseComponent::~BaseComponent()
{
}

void BaseComponent::Update()
{
}

void BaseComponent::AttachGameObject(BaseGameObject* gameObject)
{
    m_GameObject = gameObject;
}

string BaseComponent::GetName()
{
    return m_Name;
}

bool BaseComponent::IsEnable()
{
    return m_Active;
}

vector<BaseComponent*> BaseComponent::GetComponentList()
{
    return m_GameObject->m_ComponentList;
}

vector<BaseScript*> BaseComponent::GetScriptList()
{
    return m_GameObject->m_ScriptList;
}

vector<BaseShader*> BaseComponent::GetShaderList()
{
    return m_GameObject->m_ShaderList;
}
