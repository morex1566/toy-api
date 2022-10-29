////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <directxmath.h>
#include <vector>

#include "AlignedAllocationPolicy.h"
#include "d3dclass.h"
#include "GameObject.h"

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class Scene;

class Camera : public AlignedAllocationPolicy<16>, public BaseGameObject
{
public:
	Camera(D3DClass*, HWND, Scene*);
	Camera(const Camera&);
	~Camera();

public:
	void Start() override;
	void Update() override;

public:
	void GetViewMatrix(XMMATRIX&);
	XMMATRIX GetViewMatrix();
	Camera* SetAsMainCamera();

private:
	XMMATRIX m_viewMatrix;
	Scene* m_CurrentScene;
	XMMATRIX m_cameraRotationMatrix;
	XMVECTOR m_cameraTarget;
	XMVECTOR m_cameraUp;
};

#endif