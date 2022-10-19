////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include "Object.h"
#include "Component.h"
#include "Shader.h"
#include "Script.h"


Scene::Scene()
{
	m_D3D = 0;
	m_MainCamera = 0;
	m_LightShader = 0;
	m_Light = 0;
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

	// Create the camera object.
	m_MainCamera = new Camera(m_D3D, this);
	if(!m_MainCamera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_MainCamera->SetPosition(0.0f, 0.0f, -5.0f);
		

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), L"./resources/cube.obj", L"./resources/seafloor.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create Camera...
	gameObjectList.push_back(
		(new Camera(m_D3D, this))
		->SetAsMainCamera()
	);


	// Create Cube...
	gameObjectList.push_back(
		(new Object(m_D3D))
		->AddComponent(ComponentType::Mesh, "./resources/cube.obj")
		->AddComponent(ComponentType::Texture, "./resources/seafloor.dds")
		->AddShader(ShaderType::LightShader, "./shaders/color.vs", "./shaders/color.ps")
	);

	





	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(1.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	return true;
}


void Scene::Shutdown()
{
	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if(m_MainCamera)
	{
		delete m_MainCamera;
		m_MainCamera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
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

	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Update(rotation);
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

bool Scene::Update(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;
	
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_MainCamera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_MainCamera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	worldMatrix = XMMatrixRotationY(rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), 
		worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTexture(), 
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_MainCamera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	
	if(!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}