#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "Transform.h"

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
	virtual void Start() = 0;
	virtual void Update() = 0;

public:
	void AttachGameObject(BaseGameObject*);
	string GetName();
	bool IsEnable();

protected:
	vector<BaseScript*> GetScriptList();
	Transform* GetTransform();

protected:
	BaseGameObject* m_GameObject;
	string m_Name;
	bool m_Active;
};