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

void BaseScript::Initialize()
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

vector<BaseScript*> BaseScript::GetScriptList()
{
    return m_GameObject->m_ScriptList;
}
