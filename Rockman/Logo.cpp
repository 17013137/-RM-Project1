#include "stdafx.h"
#include "Logo.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "Button.h"
#include "Obj.h"
#include "ObjMgr.h"
Logo::Logo()
{
}


Logo::~Logo()
{
	Release();
}

void Logo::Initialize()
{
	bmpmgr->Insert_Bmp(L"../Image/05.Menu/MenuBack.bmp", L"LOGO");


	ScrollMgr::Get_Instance()->Set_StageSizeX(800);
	ScrollMgr::Get_Instance()->Set_StageSizeX(600);

	Obj* pObj = CAbstractFactory<Button>::Create(400.f, 400.f);
	ObjMgr::Get_Instance()->Set_Objlist(BUTTON, pObj);
}

void Logo::Update()
{
	ObjMgr::Get_Instance()->Update();
}

int Logo::Late_Update()
{

	return 0;
}

void Logo::Render(HDC hdc)
{
	HDC		hMemDC = bmpmgr->Find_Image(L"LOGO");

	BitBlt(hdc, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	ObjMgr::Get_Instance()->Render(hdc);
}

void Logo::Release()
{
}
