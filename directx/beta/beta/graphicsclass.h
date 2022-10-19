////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "utility.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class Scene
{
public:
	friend class Camera;

	Scene();
	Scene(const Scene&);
	~Scene();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	string GetName();

private:
	bool Update();

private:
	string m_Name;
	D3DClass* m_D3D;
	Camera* m_MainCamera;

	vector<BaseGameObject*> gameObjectList;
};

#endif