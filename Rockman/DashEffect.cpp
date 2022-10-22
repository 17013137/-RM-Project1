#include "stdafx.h"
#include "DashEffect.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
//64 50
DashEffect::DashEffect()
{
	player = ObjMgr::Get_Instance()->Get_Player();
	id = EFFECT;
	dir = DIR_LEFT;
	timer = 0;
}


DashEffect::~DashEffect()
{
	Release();
}

void DashEffect::Initialize()
{
	info.fcX = 64.f;
	info.fcY = 50.f;

	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 7;
	frame.frspeed = 50;
	frame.frtime = GetTickCount();
	Update_Rect();
	timer = GetTickCount();
	dir = target->Get_Dir();
	if (dir == DIR_LEFT) {
		frameKey = L"DASH_LEFT";
	}
	else {
		frameKey = L"DASH_RIGHT";
	}
}

int DashEffect::Update()
{
	info.fX = target->Get_Info().fX;
	info.fY = target->Get_RectInfo().bottom;
	if (dir == DIR_LEFT) {
		info.fX += 100.f;
	}
	else {
		info.fX -= 100.f;
	}
	
	if (frame.Start == frame.End)
		dead = true;
	if (true == dead) {
		return OBJ_DEAD;
	}

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

int DashEffect::Late_Update()
{
	return 0;
}

void DashEffect::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	//Rectangle(hdc, rectinfo.left + scrollX, rectinfo.top, rectinfo.right + scrollX, rectinfo.bottom);
	HDC memDC = bmpmgr->Find_Image(frameKey);
	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX),
		int(rectinfo.top),
		64,
		50,
		memDC,
		frame.Start * 64,
		frame.Scean * 50,
		64,
		50,
		RGB(200, 0, 255));
}

void DashEffect::Release()
{
}
