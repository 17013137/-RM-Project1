#include "stdafx.h"
#include "Bullet.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "BulletEffect.h"

Bullet::Bullet()
{
	id = BULLET;
	dir = DIR_RIGHT;
	stat.damage = 10;
	stat.maxhp = 10;
	stat.hp = 10;
}


Bullet::~Bullet()
{
	Release();
}

void Bullet::Initialize()
{
	info.fcX = 16.f;
	info.fcY = 16.f;

	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Bullet/hit_left.bmp", L"HITLEFT");
	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Bullet/hit_right.bmp", L"HITRIGHT");


	speed = 24.f;
	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 4;
	frame.frspeed = 50;
	frame.frtime = GetTickCount();
	Update_Rect();
	
}

int Bullet::Update()
{
	float Dist = fabs(ObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - info.fX);
	if (true == dead || isdamaged || CCollisionMgr::Collision_TILE(this)
		|| Dist > 450) {
		ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<BulletEffect>::Create(info.fX, info.fY, dir));
		isdamaged = false;
		return OBJ_DEAD;
	}

	switch (dir)	
	{
	case DIR_LEFT:
		frameKey = L"BULLET_LEFT";
		info.fX -= speed;
		break;
	case DIR_RIGHT:
		frameKey = L"BULLET_RIGHT";
		info.fX += speed;
		break;
	}

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

int Bullet::Late_Update()
{
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(MONSTER)); //ÃÑ¾Ë»èÁ¦
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(OBSTACLE));
	return 0;
}

void Bullet::Render(HDC hdc)
{

	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	HDC memDC = bmpmgr->Find_Image(frameKey);
	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX -8),
		int(rectinfo.top-8),
		32,
		32,
		memDC,
		frame.Start * 32,
		frame.Scean * 32,
		32,
		32,
		RGB(200, 0, 255));
}

void Bullet::Release()
{
}
