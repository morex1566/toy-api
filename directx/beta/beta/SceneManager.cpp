#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
    clearAllScene();
}

bool SceneManager::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
    Scene* menu;
    Scene* main;

    menu = new Scene;
    if (!menu)
    {
        return false;
    }

    menu->Initialize(screenWidth, screenHeight, hwnd);
    m_SceneList.push_back(menu);


    main = new Scene;
    if (!main)
    {
        return false;
    }

    main->Initialize(screenWidth, screenHeight, hwnd);
    m_SceneList.push_back(main);


    // Set main scene.
    m_CurrentScene = m_SceneList.back();

    return true;
}

Scene* SceneManager::GetCurrentScene()
{
    return m_CurrentScene;
}

void SceneManager::LoadSceneWithName(const char* name)
{
    for (auto Scene : m_SceneList)
    {
        if (Scene->GetName() == name)
        {
            delete m_CurrentScene;
            m_CurrentScene = Scene;
        }
    }
}

void SceneManager::clearAllScene()
{
    // delete all stored scene.
    for (auto scene : m_SceneList)
    {
        scene->Shutdown();
        delete scene;
    }
    m_SceneList.clear();
    vector<Scene*>().swap(m_SceneList);
}
