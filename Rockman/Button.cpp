#include "stdafx.h"
#include "Button.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
// 94 48
Button::Button()
	: id(0)
{
}


Button::~Button()
{
	Release();
}

void Button::Initialize(void)
{
	info.fcX = 148.f;
	info.fcY = 16.f;
	bmpmgr->Insert_Bmp(L"../Image/05.Menu/PressEnter.bmp", L"ENTER");
	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 1;
	frame.frspeed = 100;
	frame.frtime = GetTickCount();
	Update_Rect();
	frameKey = L"ENTER";
}

int Button::Update(void)
{
	if (KeyMgr::Get_Instance()->Key_DOWN(VK_RETURN))
	{
		SceneMgr::Get_Instance()->SceneChange(MENU);
		dead = true;
		return 0;

	}

	if (dead)
		return OBJ_DEAD;
	Update_Rect();
	Move_Frame();
	return OBJ_NOEVENT;
}

int Button::Late_Update(void)
{
	return 0;
}

void Button::Render(HDC hDC)
{
	HDC memDC = bmpmgr->Find_Image(frameKey);

	GdiTransparentBlt(hDC,
		int(rectinfo.left - 64),
		int(rectinfo.top - 8),
		296,
		32,
		memDC,
		frame.Start * 148,
		frame.Scean * 16,
		148,
		16,
		RGB(255, 0, 255));
}

void Button::Release(void)
{
}
