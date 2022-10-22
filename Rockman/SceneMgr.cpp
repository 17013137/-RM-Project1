#include "stdafx.h"
#include "SceneMgr.h"
#include "Stage.h"
#include "BossStage.h"
#include "Menu.h"
#include "Logo.h"
#include "Loading.h"
#include "Ending.h"

SceneMgr* SceneMgr::m_instance = nullptr;
SceneMgr::SceneMgr()
{
	id = STAGE;
	preid = SCENE_END;
	scene = nullptr;
}


SceneMgr::~SceneMgr()
{
	Release();
}

void SceneMgr::Initialize()
{
	scene->Initialize();
}

void SceneMgr::Update()
{
	if (scene != nullptr)
		scene->Update();

}

int SceneMgr::Late_Update()
{
	if (scene != nullptr)
		scene->Late_Update();

	return 0;
}

void SceneMgr::Render(HDC hdc)
{
	if (scene != nullptr)
		scene->Render(hdc);

}

void SceneMgr::Release()
{
	Safe_Delete(scene);
}

void SceneMgr::SceneChange(SCENEID _id)
{
	if (preid != _id) {
		if(_id != ENDING)
			Safe_Delete(scene);
		switch (_id)
		{
		case STAGE:
			scene = new Stage;
			break;
		case STAGE_BOSS:
			scene = new BossStage;
			break;
		case MENU:
			scene = new Menu;
			break;
		case LOGO:
			scene = new Logo;
			break;
		case LOADING:
			scene = new Loading;
			break;
		case ENDING:
			scene = new Ending;
			break;
		}
		scene->Initialize();
		preid = _id;
		
	}

}
