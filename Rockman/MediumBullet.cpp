#include "stdafx.h"
#include "MediumBullet.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BulletEffect.h"

MediumBullet::MediumBullet()
{
	id = BULLET;
	dir = DIR_RIGHT;
	state = STATE_END;
	stat.damage = 50;
	stat.hp = 10;
	stat.maxhp = 10;
}


MediumBullet::~MediumBullet()
{
	Release();
}

void MediumBullet::Initialize()
{
	info.fcX = 96.f;
	info.fcY = 64.f;

	speed = 24.f;
	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 3;
	frame.frspeed = 50;
	frame.frtime = GetTickCount();
	Update_Rect();

}

int MediumBullet::Update()
{
	
	float Dist = fabs(ObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - info.fX);
	if (true == dead || isdamaged || CCollisionMgr::Collision_TILE(this) ||
		Dist > 450) {
		float x = (dir == DIR_LEFT) ? -30.f : 30.f;
		ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<BulletEffect>::Create(info.fX+x, info.fY, dir));
		return OBJ_DEAD;
	}
	switch (dir)
	{
	case DIR_LEFT:
		frameKey = L"MEDIUM_BULLET_LEFT";
		info.fX -= speed;
		break;
	case DIR_RIGHT:
		frameKey = L"MEDIUM_BULLET_RIGHT";
		info.fX += speed;
		break;
	}

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

int MediumBullet::Late_Update()
{
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(MONSTER));
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(OBSTACLE));
	//ÃÑ¾Ë»èÁ¦
	return 0;
}

void MediumBullet::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	HDC memDC = bmpmgr->Find_Image(frameKey);
	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX),
		int(rectinfo.top),
		96,
		64,
		memDC,
		frame.Start * 48,
		frame.Scean * 32,
		48,
		32,
		RGB(200, 0, 255));
}

void MediumBullet::Release()
{
}
