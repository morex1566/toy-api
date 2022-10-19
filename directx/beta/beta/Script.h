#pragma once
#include <string>
#include <vector>
#include "Component.h"

using namespace std;

class BaseGameObject;

class BaseScript
{
public:
	friend class BaseComponent;

	BaseScript();
	BaseScript(BaseGameObject*);
	virtual ~BaseScript();

public:
	virtual void Initialize();
	virtual void Update();

public:
	string GetName();
	bool IsEnable();

protected:
	vector<BaseScript*> GetScriptList();

protected:
	BaseGameObject* m_GameObject;
	string m_Name;
	bool m_Active;
};