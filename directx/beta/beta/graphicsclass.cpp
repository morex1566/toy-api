////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include "Object.h"
#include "Component.h"
#include "Shader.h"
#include "Script.h"
#include "Object1.h"
#include "Object2.h"	


Scene::Scene()
{
	m_D3D = 0;
	m_MainCamera = 0;
}


Scene::Scene(const Scene& other)
{
}


Scene::~Scene()
{
}


bool Scene::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}
		
	// Create Camera...
	gameObjectList.push_back(
		(new Camera(m_D3D, hwnd, this))
		->SetAsMainCamera()
	);

	// Create Cube...
	gameObjectList.push_back(
		(new Object(m_D3D, hwnd))
		->AddComponent(ComponentType::Mesh, "./resources/cube.obj")
		->AddComponent(ComponentType::Texture, "./resources/seafloor.dds")
		->AddScript(new Object1)
		->AddShader(ShaderType::LightShader, "./shaders/light.vs", "./shaders/light.ps")
	);

	// Create Cube...
	gameObjectList.push_back(
		(new Object(m_D3D, hwnd))
		->AddComponent(ComponentType::Mesh, "./resources/cube.obj")
		->AddComponent(ComponentType::Texture, "./resources/seafloor.dds")
		->AddScript(new Object2)
		->AddShader(ShaderType::LightShader, "./shaders/light.vs", "./shaders/light.ps")
	);

	// Create Light
	gameObjectList.push_back(
		(new Light(m_D3D, hwnd))
	);

	// Create Terrain
	gameObjectList.push_back(
		(new Object(m_D3D, hwnd))
		->AddComponent(ComponentType::Mesh, "./resources/terrain.obj")
		->AddComponent(ComponentType::Texture, "./resources/terrain.dds")
		->AddShader(ShaderType::LightShader, "./shaders/light.vs", "./shaders/light.ps")
	);

	for (auto gameObject : gameObjectList)
	{
		gameObject->Start();
	}

	return true;
}


void Scene::Shutdown()
{
	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the bunch of gameObject.
	for (auto gameObject : gameObjectList)
	{
		delete gameObject;
	}

	gameObjectList.clear();
	vector<BaseGameObject*>().swap(gameObjectList);
	
	return;
}

bool Scene::Frame()
{
	bool result;

	// Render the graphics scene.
	result = Update();
	if(!result)
	{
		return false;
	}

	return true;
}

string Scene::GetName()
{
	return m_Name;
}

bool Scene::Update()
{	
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	for (auto gameObject : gameObjectList)
	{
		gameObject->Update();
	}

	for (auto gameObject : gameObjectList)
	{
		gameObject->Render(gameObjectList, m_MainCamera);
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}
