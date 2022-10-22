#include "stdafx.h"
#include "ChargeEffect.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"

ChargeEffect::ChargeEffect()
{
	id = EFFECT;
	dir = DIR_LEFT;
	timer = 0;
}


ChargeEffect::~ChargeEffect()
{
	Release();
}

void ChargeEffect::Initialize()
{
	info.fcX = 150.f;
	info.fcY = 150.f;

	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 3;
	frame.frspeed = 50;
	frame.frtime = GetTickCount();
	Update_Rect();
	timer = GetTickCount();
	if (dir == DIR_LEFT) {
		frameKey = L"CHARGE_HIT_RIGHT";
		info.fX -= 50.f;
	}
	else {
		frameKey = L"CHARGE_HIT_LEFT";
		info.fX += 50.f;
	}
}

int ChargeEffect::Update()
{
	
	if (frame.Start == frame.End)
		dead = true;
	if (true == dead) {
		return OBJ_DEAD;
	}

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

int ChargeEffect::Late_Update()
{
	return 0;
}

void ChargeEffect::Render(HDC hdc)
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

void ChargeEffect::Release()
{
}
