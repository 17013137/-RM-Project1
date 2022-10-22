#include "stdafx.h"
#include "SelectButton.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
//94 16
SelectButton::SelectButton()
	:id(0)
{
}


SelectButton::~SelectButton()
{
	Release();
}

void SelectButton::Initialize(void)
{
	info.fcX = 188.f;
	info.fcY = 96.f;
	bmpmgr->Insert_Bmp(L"../Image/05.Menu/MenuSelect.bmp", L"MENUSELECT");
	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 2;
	frame.frspeed = 100;
	frame.frtime = GetTickCount();
	Update_Rect();
	frameKey = L"MENUSELECT";
}

int SelectButton::Update(void)
{
	if (dead)
		return OBJ_DEAD;

	Key_input();
	Update_Rect();
	return OBJ_NOEVENT;
}

int SelectButton::Late_Update(void)
{
	return 0;
}

void SelectButton::Render(HDC hDC)
{
	HDC memDC = bmpmgr->Find_Image(frameKey);
	//Rectangle(hDC, rectinfo.left, rectinfo.top, rectinfo.right, rectinfo.bottom);
	GdiTransparentBlt(hDC,
		int(rectinfo.left),
		int(rectinfo.top),
		188,
		96,
		memDC,
		frame.Start * 94,
		frame.Scean * 48,
		94,
		48,
		RGB(255, 0, 255));
}

void SelectButton::Release(void)
{
}

void SelectButton::Key_input()
{
	if (KeyMgr::Get_Instance()->Key_DOWN(VK_DOWN) && id < 2) {
		id++;
	}

	if (KeyMgr::Get_Instance()->Key_DOWN(VK_UP) && id > 0) {
		id--;
	}
	frame.Start = id;

	if (KeyMgr::Get_Instance()->Key_DOWN(VK_RETURN))
	{
		switch (id)
		{
		case 0:
			SceneMgr::Get_Instance()->SceneChange(STAGE);
			break;
		}
		dead = true;
	}
}
