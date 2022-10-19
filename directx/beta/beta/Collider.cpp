#include "Collider.h"

Collider::Collider(BaseGameObject* gameObject)
	: BaseComponent(gameObject)
{
	m_Name = "Collider";
	m_Active = true;
}

Collider::~Collider()
{
}
