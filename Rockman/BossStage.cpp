#include "stdafx.h"
#include "BossStage.h"
#include "TileMgr.h"
#include "CollisionMgr.h"
#include "Monster.h"
#include "Gunman.h"
#include "Enum.h"
#include "ScrollMgr.h"
#include "ST1Boss.h"
#include "BossHp.h"

BossStage::BossStage()
{
	objmgr = ObjMgr::Get_Instance();
	uimgr = UIMgr::Get_Instance();
}


BossStage::~BossStage()
{
	Release();
}

void BossStage::Initialize()
{
	ScrollMgr::Get_Instance()->Set_StageSizeX(1800.f);
	ScrollMgr::Get_Instance()->Set_StageSizeY(600.f);


	Obj* pobj = CAbstractFactory<ST1Boss>::Create(1000, 300);
	objmgr->Set_Objlist(MONSTER, pobj);
	uimgr->Add_Objlist(BOSS_HP, CAbstractFactory<BossHp>::Create(0, 0, pobj));
	//CTileMgr::Get_Instance()->Initialize();
	CTileMgr::Get_Instance()->Load_Data(STAGE_BOSS);
	BmpMgr::Get_Instance()->Insert_Bmp(L"../Image/00.Map/Stage1Boss.bmp", L"STAGE1_BOSS");

}

void BossStage::Update()
{
	objmgr->Update();
	uimgr->Update();
	CTileMgr::Get_Instance()->Update();
}

int BossStage::Late_Update()
{
	objmgr->Late_Update();
	uimgr->Late_Update();
	ScrollMgr::Get_Instance()->Scroll_Lock();
	CTileMgr::Get_Instance()->Late_Update();
	return 0;
}

void BossStage::Render(HDC hdc)
{
	int	iScrollX = (int)ScrollMgr::Get_Instance()->Get_ScrollX();
	HDC		hMemDC = BmpMgr::Get_Instance()->Find_Image(L"STAGE1_BOSS");
	BitBlt(hdc, iScrollX, 0, 1800, 600, hMemDC, 0, 0, SRCCOPY);
	objmgr->Render(hdc);
	uimgr->Render(hdc);
	//CTileMgr::Get_Instance()->Render(hdc);
}

void BossStage::Release()
{
	CTileMgr::Get_Instance()->Destroy_Instance();
	ObjMgr::Get_Instance()->Delete_ID(MONSTER);
	ObjMgr::Get_Instance()->Delete_ID(BULLET);
	uimgr->Delete_UI(PLAYER_HP);
}

void BossStage::offset()
{
}
