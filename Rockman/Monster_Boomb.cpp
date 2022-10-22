#include "stdafx.h"
#include "Monster_Boomb.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"
#include "ExplosionEffect.h"

Monster_Boomb::Monster_Boomb()
{
	id = MONSTER_BULLET;
	dir = DIR_LEFT;
	stat.damage = 10;
	stat.maxhp = 10;
	stat.hp = 10;
}


Monster_Boomb::~Monster_Boomb()
{
	Release();
}

void Monster_Boomb::Initialize()
{
	info.fcX = 32.f;
	info.fcY = 32.f;
	frameKey = L"GUNMAN_BULLET";
	speed = 10.f;
	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 3;
	frame.frspeed = 50;
	frame.frtime = GetTickCount();
	Update_Rect();

}

int Monster_Boomb::Update()
{
	float Dist = fabs(ObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - info.fX);
	if (true == dead || isdamaged || CCollisionMgr::Collision_TILE(this)
		|| Dist > 500) {
		isdamaged = false;
		return OBJ_DEAD;
	}

	switch (dir)
	{
	case DIR_LEFT:
		info.fX -= speed;
		break;
	case DIR_RIGHT:
		info.fX += speed;
		break;
	}

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

int Monster_Boomb::Late_Update()
{
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(PLAYER));
	return 0;
}

void Monster_Boomb::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	HDC memDC = bmpmgr->Find_Image(frameKey);
	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX),
		int(rectinfo.top),
		32,
		32,
		memDC,
		frame.Start * 32,
		frame.Scean * 32,
		32,
		32,
		RGB(200, 0, 255));

}

void Monster_Boomb::Release()
{
}
