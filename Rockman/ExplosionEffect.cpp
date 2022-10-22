#include "stdafx.h"
#include "ExplosionEffect.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
// 170 170  17°³
ExplosionEffect::ExplosionEffect()
{
	id = EFFECT;
	dir = DIR_LEFT;
	timer = 0;
}


ExplosionEffect::~ExplosionEffect()
{
	Release();
}

void ExplosionEffect::Initialize()
{
	info.fcX = 170.f;
	info.fcY = 170.f;

	frameKey = L"EXPLOSION";
	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 17;
	frame.frspeed = 50;
	frame.frtime = GetTickCount();
	Update_Rect();
	timer = GetTickCount();
}

int ExplosionEffect::Update()
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

int ExplosionEffect::Late_Update()
{
	return 0;
}

void ExplosionEffect::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	//Rectangle(hdc, rectinfo.left + scrollX, rectinfo.top, rectinfo.right + scrollX, rectinfo.bottom);
	HDC memDC = bmpmgr->Find_Image(frameKey);
	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX),
		int(rectinfo.top),
		170,
		170,
		memDC,
		frame.Start * 170,
		frame.Scean * 170,
		170,
		170,
		RGB(200, 0, 255));
}

void ExplosionEffect::Release()
{
}
