#include "stdafx.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "Enum.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "Ending.h"
MainGame::MainGame()
	:m_iFPS(0), m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * 32);
	hdc = GetDC(g_hwnd);

}


MainGame::~MainGame()
{
	Release();
}

void MainGame::Initialize()
{
	BmpMgr::Get_Instance()->Insert_Bmp(L"../Image/00.Map/Back.bmp", L"Back");
	//SceneMgr::Get_Instance()->SceneChange(SCENEID(STAGE));
	SceneMgr::Get_Instance()->SceneChange(SCENEID(LOGO));
	
}

void MainGame::Update()
{
	SceneMgr::Get_Instance()->Update();

}

int MainGame::Late_Update()
{
	SceneMgr::Get_Instance()->Late_Update();
	ScrollMgr::Get_Instance()->Scroll_Lock();

	return 0;
}

void MainGame::Render()
{
	//Rectangle(hdc, 0, 0, WINCX, WINCY);
	//LineMgr::Get_Instance()->Render(hdc);
	//	SceneMgr::Get_Instance()->Render(hdc);
	HDC		hBackBufferDC = BmpMgr::Get_Instance()->Find_Image(L"Back");
	if (ENDING == SceneMgr::Get_Instance()->Get_Scene())
		return;

	SceneMgr::Get_Instance()->Render(hBackBufferDC);
	//TCHAR		szBuff[32] = L"";
	//++m_iFPS;
	//
	//if (m_dwTime + 1000 < GetTickCount())
	//{
	//	swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
	//	SetWindowText(g_hwnd, m_szFPS);
	//
	//	m_iFPS = 0;
	//	m_dwTime = GetTickCount();
	//}
	/*

	TCHAR		szBuff[32] = L"";

	swprintf_s(szBuff, L"HP : %f", (Hp/100)*90);
	SetWindowText(g_hwnd, szBuff);

	*/
	BitBlt(hdc, 0, 0, WINCX, WINCY, hBackBufferDC, 0, 0, SRCCOPY);

}

void MainGame::Release()
{
	KeyMgr::Get_Instance()->Destroy_Instance();
	ScrollMgr::Get_Instance()->Destory_Instance();
	BmpMgr::Get_Instance()->Destory_Instance();
	SceneMgr::Get_Instance()->Destroy_Instance();

	ReleaseDC(g_hwnd, hdc);
}
