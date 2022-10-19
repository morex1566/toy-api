#pragma once
#include "graphicsclass.h"
#include "utility.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;

	bool Initialize(int, int, HWND);

	Scene* GetCurrentScene();
	void LoadSceneWithName(const char*);

private:
	void clearAllScene();

private:
	Scene* m_CurrentScene;
	vector<Scene*> m_SceneList;
};

