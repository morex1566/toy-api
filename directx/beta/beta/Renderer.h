#pragma once
#include "Component.h"

class Renderer : public BaseComponent
{
public:
	Renderer(BaseGameObject*);
	~Renderer();

public:
	void Initialize() override;
	void Update() override;
	void Render();

private:
	virtual void renderMesh();
	virtual void renderShader();
};

