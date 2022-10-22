#include "stdafx.h"
#include "Loading.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "Player.h"

Loading::Loading()
{
}


Loading::~Loading()
{
	Release();
}

void Loading::Initialize()
{
	ScrollMgr::Get_Instance()->Set_StageSizeX(800);
	ScrollMgr::Get_Instance()->Set_StageSizeX(600);
	ObjMgr::Get_Instance()->Set_PlayerInfo(100.f, 200.f);
	bmpmgr->Insert_Bmp(L"../Image/05.Menu/Loading.bmp", L"LOADING");
	//if (ObjMgr::Get_Instance()->Get_Player() == nullptr) {
	//	Obj* pobj = CAbstractFactory<Player>::Create();
	//	ObjMgr::Get_Instance()->Set_Objlist(PLAYER, pobj);
	//}
}


void Loading::Update()
{
	if (KeyMgr::Get_Instance()->Key_DOWN(VK_RETURN))
	{
		SceneMgr::Get_Instance()->SceneChange(STAGE_BOSS);

	}
}

int Loading::Late_Update()
{
	return 0;
}

void Loading::Render(HDC hdc)
{
	HDC		hMemDC = bmpmgr->Find_Image(L"LOADING");

	BitBlt(hdc, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	//ObjMgr::Get_Instance()->Render(hdc);
}

void Loading::Release()
{
}
