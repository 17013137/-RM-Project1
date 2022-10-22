#include "stdafx.h"
#include "MiddleCharge.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
// 200 200
MiddleCharge::MiddleCharge()
{
	id = EFFECT;
	dir = DIR_LEFT;
	timer = 0;
}


MiddleCharge::~MiddleCharge()
{
	Release();
}

void MiddleCharge::Initialize()
{
	info.fcX = 200.f;
	info.fcY = 200.f;

	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 7;
	frame.frspeed = 100;
	frame.frtime = GetTickCount();
	Update_Rect();
	frameKey = L"CHARGE";
	//timer = GetTickCount();
}

int MiddleCharge::Update()
{
	info.fX = target->Get_Info().fX;
	info.fY = target->Get_Info().fY;
	if (true == dead) {
		return OBJ_DEAD;
	}

	if (frame.Start == frame.End) {
		frame.Start = 0;
	}

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

int MiddleCharge::Late_Update()
{
	return 0;
}

void MiddleCharge::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	//Rectangle(hdc, rectinfo.left + scrollX, rectinfo.top, rectinfo.right + scrollX, rectinfo.bottom);
	HDC memDC = bmpmgr->Find_Image(frameKey);
	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX),
		int(rectinfo.top),
		200,
		200,
		memDC,
		frame.Start * 200,
		frame.Scean * 200,
		200,
		200,
		RGB(200, 0, 255));
}

void MiddleCharge::Release()
{
}
