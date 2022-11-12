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
#include "Bitmap.h"

#include "Skydome.h"
#include "SkydomeSetupScript.h"
#include "skydomeshaderclass.h"

#include "Cloud.h"
#include "CloudSetupScript.h"

#include "UI.h"

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

	m_RootGameObject = new BaseGameObject(m_D3D, hwnd);
	if (!m_RootGameObject)
	{
		return false;
	}

	// Create Camera...
	m_RootGameObject->CreateGameObject((new Camera(m_D3D, hwnd, this))
		->SetAsMainCamera()
		->AddScript(new FPSCameraScript)
	);


	// Create Cube...
	m_RootGameObject->CreateGameObject(
		(new Object(m_D3D, hwnd))
		->AddComponent(ComponentType::Mesh, "./resources/cube.obj")
		->AddComponent(ComponentType::Texture, "./resources/seafloor.dds")
		->AddScript(new Object1)
		->AddShader(ShaderType::LightShader, "./shaders/light.vs", "./shaders/light.ps")
	);

	// Create Cube...
	m_RootGameObject->CreateGameObject(
		(new Object(m_D3D, hwnd))
		->AddComponent(ComponentType::Mesh, "./resources/cube.obj")
		->AddComponent(ComponentType::Texture, "./resources/seafloor.dds")
		->AddScript(new Object2)
		->AddShader(ShaderType::LightShader, "./shaders/light.vs", "./shaders/light.ps")
	);

	// Create enviroment light...
	m_RootGameObject->CreateGameObject(
		(new Light(m_D3D, hwnd))
	);

	//// Create Skydome...
	//gameObjectList.push_back(
	//	(new Skydome(m_D3D, hwnd))
	//	->AddComponent(ComponentType::Mesh, "./resources/sphere.obj")
	//	->AddScript(new SkydomeSetupScript(m_MainCamera))
	//	->AddShader(ShaderType::SkydomeShader, "./shaders/skydome.vs", "./shaders/skydome.ps")
	//);

	//// Create Cloud
	//gameObjectList.push_back(
	//	(new Cloud(m_D3D, hwnd))
	//	->AddComponent(ComponentType::Mesh, "./resources/cloudplane.obj")
	//	->AddScript(new SkyplaneSetupScript(m_MainCamera))
	//	->AddShader(ShaderType::SkyplaneShader, "./shaders/skyplane.vs", "./shaders/skyplane.ps")
	//);

	// Create Terrains
	m_RootGameObject->CreateGameObject(
		(new Terrain(m_D3D, hwnd))
		->AddComponent(new Bitmap("./resources/heightmap.bmp", "./resources/grass.dds", "./resources/slope.dds", "./resources/rock.dds"))
		->AddShader(ShaderType::TerrainShader, "./shaders/terrain.vs", "./shaders/terrain.ps")
	);

	// Create text
	m_text = dynamic_cast<TextClass*>(
		new TextClass(m_D3D, hwnd, "./resources/fontdata.txt", "./resources/font.dds", "./shaders/font.vs", "./shaders/font.ps",
		screenWidth, screenHeight)
		);

	for (auto gameObject : m_RootGameObject->GetGameObjectList())
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
	for (auto gameObject : m_RootGameObject->GetGameObjectList())
	{
		delete gameObject;
	}
	
	return;
}

bool Scene::Frame(int fps, int cpu, int time)
{
	bool result;

	// Set the frames per second.
	result = m_text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

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

bool Scene::Start()
{
	return false;
}

bool Scene::Update()
{	
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// set ui layer position
	Transform* transfrom = m_text->GetTransform();
	transfrom->SetPosition(m_MainCamera->GetTransform()->GetPosition());
	transfrom->SetRotation(m_MainCamera->GetTransform()->GetRotation());
	m_text->GetTransform()->MoveByLocal(XMFLOAT3(0, 0, 2));

	// game objects collision check


	// game objects physics check


	// game objects script udpate
	for (auto gameObject : m_RootGameObject->GetGameObjectList())
	{
		gameObject->Update();
	}

	m_D3D->TurnOffCulling();
	m_D3D->TurnOffZBuffer();

	// game objects no z buffer rendering
	for (auto gameObject : m_RootGameObject->GetGameObjectList())
	{
		if (gameObject->GetLayer() == LayerType::BackGround)
		{
			gameObject->Render(m_RootGameObject->GetGameObjectList(), m_MainCamera);
		}
	}

	m_D3D->EnableSecondBlendState();

	// game objects with z buffer rendering
	for (auto gameObject : m_RootGameObject->GetGameObjectList())
	{
		if (gameObject->GetLayer() == LayerType::Blend)
		{
			gameObject->Render(m_RootGameObject->GetGameObjectList(), m_MainCamera);
		}
	}

	m_D3D->TurnOffAlphaBlending();
	m_D3D->TurnOnCulling();
	m_D3D->TurnOnZBuffer();


	for (auto gameObject : m_RootGameObject->GetGameObjectList())
	{
		if (gameObject->GetLayer() == LayerType::Base)
		{
			gameObject->Render(m_RootGameObject->GetGameObjectList(), m_MainCamera);
		}
	}

	m_D3D->TurnOffZBuffer();
	m_D3D->TurnOnAlphaBlending();
	// ui text rendering
	m_text->Render(m_D3D->GetDeviceContext(), m_text->GetTransform()->GetWorldMatrix(), m_MainCamera->GetViewMatrix(), m_D3D->GetOrthoMatrix());

	m_D3D->TurnOnZBuffer();
	m_D3D->TurnOffAlphaBlending();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool Scene::Render()
{
	return false;
}
