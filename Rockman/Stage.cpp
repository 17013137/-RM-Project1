#include "stdafx.h"
#include "Stage.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "TileMgr.h"
#include "CollisionMgr.h"
#include "LineMgr.h"
#include "Monster.h"
#include "Gunman.h"
#include "MapObj.h"
#include "Boss_obs.h"
#include "Boss_Attack.h"
#include "PlayerHP.h"


Stage::Stage()
{
	objmgr = ObjMgr::Get_Instance();
	uimgr = UIMgr::Get_Instance();
}


Stage::~Stage()
{
	Release();
}

void Stage::Initialize()
{
	ScrollMgr::Get_Instance()->Set_StageSizeX(10876.f);
	ScrollMgr::Get_Instance()->Set_StageSizeY(856.f);
	Obj* pobj = CAbstractFactory<Player>::Create();
	objmgr->Set_Objlist(PLAYER, pobj);
	objmgr->Set_Objlist(OBSTACLE, CAbstractFactory<MapObj>::Create(4215, 400)); //4215 장애물 높이 400고정 간격:1275
	objmgr->Set_Objlist(OBSTACLE, CAbstractFactory<MapObj>::Create(5490, 400));
	objmgr->Set_Objlist(OBSTACLE, CAbstractFactory<MapObj>::Create(6765, 400));
	objmgr->Set_Objlist(OBSTACLE, CAbstractFactory<MapObj>::Create(8040, 400));
	objmgr->Set_Objlist(MONSTER, CAbstractFactory<Monster>::Create(2000, 200));
	objmgr->Set_Objlist(MONSTER, CAbstractFactory<Monster>::Create(2500, 200));
	objmgr->Set_Objlist(MONSTER, CAbstractFactory<Monster>::Create(3500, 200));
	objmgr->Set_Objlist(MONSTER, CAbstractFactory<Monster>::Create(4000, 200));
	objmgr->Set_Objlist(MONSTER, CAbstractFactory<Gunman>::Create(8500, 200));
	objmgr->Set_Objlist(MONSTER, CAbstractFactory<Gunman>::Create(8700, 200));
	objmgr->Set_Objlist(MONSTER, CAbstractFactory<Boss_obs>::Create(4000, 100));
	uimgr->Add_Objlist(PLAYER_HP, CAbstractFactory<PlayerHP>::Create());

	CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Data(STAGE);
	LineMgr::Get_Instance()->Initialize();
	BmpMgr::Get_Instance()->Insert_Bmp(L"../Image/00.Map/Stage1.bmp", L"Stage1");
	BmpMgr::Get_Instance()->Insert_Bmp(L"../Image/00.Map/Stage1_Near.bmp", L"Stage1_Near");
}

void Stage::Update()
{
	uimgr->Update();
	objmgr->Update();
	CTileMgr::Get_Instance()->Update();
}

int Stage::Late_Update()
{
	objmgr->Late_Update();
	uimgr->Late_Update();
	ScrollMgr::Get_Instance()->Scroll_Lock();
	CTileMgr::Get_Instance()->Late_Update();
	return 0;
}

void Stage::Render(HDC hdc)
{
	int	iScrollX = (int)ScrollMgr::Get_Instance()->Get_ScrollX();
	HDC		hMemDC = BmpMgr::Get_Instance()->Find_Image(L"Stage1");
	BitBlt(hdc, iScrollX, 0, 10876, 856, hMemDC, 0, 0, SRCCOPY);
	objmgr->Render(hdc);
	HDC		hMemDC2 = BmpMgr::Get_Instance()->Find_Image(L"Stage1_Near"); //원근장애물
	GdiTransparentBlt(hdc,
		iScrollX,
		0,
		10876,
		856,
		hMemDC2,
		0,
		0,
		10876,
		856,
		RGB(255, 0, 255));

	uimgr->Render(hdc);
	//CTileMgr::Get_Instance()->Render(hdc);
	//LineMgr::Get_Instance()->Render(hdc);

}

void Stage::Release()
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	ObjMgr::Get_Instance()->Delete_ID(MONSTER);
	ObjMgr::Get_Instance()->Delete_ID(BULLET);
}
