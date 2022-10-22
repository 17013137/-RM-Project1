#include "stdafx.h"
#include "FullCharge.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
//150 150
FullCharge::FullCharge()
{
	id = EFFECT;
	dir = DIR_LEFT;
	timer = 0;
}


FullCharge::~FullCharge()
{
	Release();
}

void FullCharge::Initialize()
{
	info.fcX = 150.f;
	info.fcY = 150.f;

	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 4;
	frame.frspeed = 200;
	frame.frtime = GetTickCount();
	Update_Rect();
	frameKey = L"FULLCHARGE11";
}

int FullCharge::Update()
{
	info.fX = target->Get_Info().fX;
	info.fY = target->Get_Info().fY;
	//if (frame.Start == frame.End)
	//	dead = true;

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

int FullCharge::Late_Update()
{
	return 0;
}

void FullCharge::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	//Rectangle(hdc, rectinfo.left + scrollX, rectinfo.top, rectinfo.right + scrollX, rectinfo.bottom);
	HDC memDC = bmpmgr->Find_Image(frameKey);
	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX),
		int(rectinfo.top),
		150,
		150,
		memDC,
		frame.Start * 150,
		frame.Scean * 150,
		150,
		150,
		RGB(200, 0, 255));
}

void FullCharge::Release()
{
}
