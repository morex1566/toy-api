#pragma once
#include "Component.h"

class Camera;

class Renderer : public BaseComponent
{
public:
	Renderer(BaseGameObject*);
	~Renderer();

public:
	void Update() override;
	void Render(vector<BaseGameObject*>, Camera*);

private:
	virtual void renderMesh();
	virtual void renderShader(vector<BaseGameObject*>, Camera*);
};

