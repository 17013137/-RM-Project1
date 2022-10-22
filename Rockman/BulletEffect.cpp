#include "stdafx.h"
#include "BulletEffect.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
//150 150
BulletEffect::BulletEffect()
{
	id = EFFECT;
	dir = DIR_LEFT;
	timer = 0;
}


BulletEffect::~BulletEffect()
{
	Release();
}

void BulletEffect::Initialize()
{
	info.fcX = 150.f;
	info.fcY = 150.f;

	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 3;
	frame.frspeed = 100;
	frame.frtime = GetTickCount();
	Update_Rect();
	timer = GetTickCount();
	if (dir == DIR_LEFT) {
		frameKey = L"HITRIGHT";
	}
	else {
		frameKey = L"HITLEFT";
	}
}

int BulletEffect::Update()
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

int BulletEffect::Late_Update()
{
	return 0;
}

void BulletEffect::Render(HDC hdc)
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

void BulletEffect::Release()
{
}
