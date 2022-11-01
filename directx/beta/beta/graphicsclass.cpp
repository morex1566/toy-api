////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include "Component.h"
#include "Shader.h"
#include "Script.h"

#include "Object.h"
#include "Object1.h"
#include "Object2.h"	

#include "FPSCameraScript.h"

#include "Terrain.h"

#include "Skydome.h"
#include "SkydomeSetupScript.h"
#include "skydomeshaderclass.h"

#include "Cloud.h"
#include "CloudSetupScript.h"

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
		->AddScript(new FPSCameraScript)
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

	// Create enviroment light...
	gameObjectList.push_back(
		(new Light(m_D3D, hwnd))
	);

	// Create Terrain...
	gameObjectList.push_back(
		(new Object(m_D3D, hwnd))
		->AddComponent(ComponentType::Mesh, "./resources/terrain.obj")
		->AddComponent(ComponentType::Texture, "./resources/terrain.dds")
		->AddShader(ShaderType::LightShader, "./shaders/light.vs", "./shaders/light.ps")
	);

	// Create Skydome...
	gameObjectList.push_back(
		(new Skydome(m_D3D, hwnd))
		->AddComponent(ComponentType::Mesh, "./resources/sphere.obj")
		->AddScript(new SkydomeSetupScript(m_MainCamera))
		->AddShader(ShaderType::SkydomeShader, "./shaders/skydome.vs", "./shaders/skydome.ps")
	);

	// Create Cloud
	gameObjectList.push_back(
		(new Cloud(m_D3D, hwnd))
		->AddComponent(ComponentType::Mesh, "./resources/cloudplane.obj")
		->AddScript(new SkyplaneSetupScript(m_MainCamera))
		->AddShader(ShaderType::SkyplaneShader, "./shaders/skyplane.vs", "./shaders/skyplane.ps")
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

bool Scene::Frame(int mouseX, int mouseY)
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

	m_D3D->TurnOffCulling();
	m_D3D->TurnOffZBuffer();

	for (auto gameObject : gameObjectList)
	{
		if (gameObject->GetLayer() == LayerType::BackGround)
		{
			gameObject->Render(gameObjectList, m_MainCamera);
		}
	}

	m_D3D->EnableSecondBlendState();

	for (auto gameObject : gameObjectList)
	{
		if (gameObject->GetLayer() == LayerType::Blend)
		{
			gameObject->Render(gameObjectList, m_MainCamera);
		}
	}

	m_D3D->TurnOffAlphaBlending();
	m_D3D->TurnOnCulling();
	m_D3D->TurnOnZBuffer();


	for (auto gameObject : gameObjectList)
	{
		if (gameObject->GetLayer() == LayerType::Base)
		{
			gameObject->Render(gameObjectList, m_MainCamera);
		}
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}
