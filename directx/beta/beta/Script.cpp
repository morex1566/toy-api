#include "Script.h"
#include "GameObject.h"

BaseScript::BaseScript()
{
}

BaseScript::BaseScript(BaseGameObject* gameObject)
{
    m_GameObject = gameObject;
}

BaseScript::~BaseScript()
{
}

void BaseScript::Start()
{
}

void BaseScript::Update()
{
}

string BaseScript::GetName()
{
    return m_Name;
}

bool BaseScript::IsEnable()
{
    return m_Active;
}

void BaseScript::AttachGameObject(BaseGameObject* gameObject)
{
    m_GameObject = gameObject;
}

vector<BaseScript*> BaseScript::GetScriptList()
{
    return m_GameObject->m_ScriptList;
}

Transform* BaseScript::GetTransform()
{
    return m_GameObject->m_Transform;
}
