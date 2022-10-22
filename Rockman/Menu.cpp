#include "stdafx.h"
#include "Menu.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "SelectButton.h"
#include "Obj.h"
#include "ObjMgr.h"

Menu::Menu()
{
}


Menu::~Menu()
{

	Release();
}

void Menu::Initialize()
{
	bmpmgr->Insert_Bmp(L"../Image/05.Menu/MenuBack.bmp", L"LOGO");

	ScrollMgr::Get_Instance()->Set_StageSizeX(800);
	ScrollMgr::Get_Instance()->Set_StageSizeX(600);

	select = CAbstractFactory<SelectButton>::Create(400.f, 400.f);
	ObjMgr::Get_Instance()->Set_Objlist(BUTTON, select);
}

void Menu::Update()
{
	ObjMgr::Get_Instance()->Update();
}

int Menu::Late_Update()
{
	return 0;
}

void Menu::Render(HDC hdc)
{
	HDC		hMemDC = bmpmgr->Find_Image(L"LOGO");

	BitBlt(hdc, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
	ObjMgr::Get_Instance()->Render(hdc);
}

void Menu::Release()
{
}
