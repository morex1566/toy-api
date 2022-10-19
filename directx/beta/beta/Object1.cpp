#include "Object1.h"

Object1::Object1()
	: BaseScript()
{
}

Object1::Object1(BaseGameObject* gameObject)
	: BaseScript(gameObject)
{
}

Object1::~Object1()
{
}

void Object1::Start()
{
	GetTransform()->TranslateAt(XMFLOAT3(0.0f, 0.1f, 0.0f));
}

void Object1::Update()
{
	rotation += 0.01f;


	GetTransform()->Transpose(GetTransform()->GetPosition(),
		XMFLOAT3(0.0f, rotation, 0.0f),
		GetTransform()->GetScale());
}
