#pragma once
#include "Scene.h"
class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();

public:
	void Initialize();
	void Update();
	int Late_Update();
	void Render(HDC hdc);
	void Release();

public:
	static SceneMgr* Get_Instance() {
		if (m_instance == nullptr)
			m_instance = new SceneMgr;

		return m_instance;
	}

	static void Destroy_Instance() {
		if (m_instance != nullptr)
			delete m_instance;
	}

	void SceneChange(SCENEID preid);
	SCENEID Get_Scene() { return preid; }
private:
	static SceneMgr* m_instance;
	Scene* scene;
	SCENEID id;
	SCENEID preid;
};

