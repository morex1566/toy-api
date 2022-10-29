#include "Object2.h"

Object2::Object2()
	: BaseScript()
{
}

Object2::Object2(BaseGameObject* gameObject)
	: BaseScript(gameObject)
{
}

Object2::~Object2()
{
}

void Object2::Start()
{
	GetTransform()->TranslateAt(XMFLOAT3(0.0f, -1.0f, 0.0f));
}

void Object2::Update()
{
	rotation -= 0.01f;

	GetTransform()->RotateAt(XMFLOAT3(0, rotation, 0));
}
