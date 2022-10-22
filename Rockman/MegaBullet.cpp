#include "stdafx.h"
#include "MegaBullet.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "ChargeEffect.h"
MegaBullet::MegaBullet()
{
	id = BULLET;
	dir = DIR_RIGHT;
	state = STATE_END;
	stat.damage = 100;
	stat.hp = 10;
	stat.maxhp = 10;
}


MegaBullet::~MegaBullet()
{
	Release();
}

void MegaBullet::Initialize()
{
	info.fcX = 128.f;
	info.fcY = 96.f;

	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Bullet/charge_hit_left.bmp", L"CHARGE_HIT_LEFT");
	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Bullet/charge_hit_right.bmp", L"CHARGE_HIT_RIGHT");

	speed = 24.f;
	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 2;
	frame.frspeed = 50;
	frame.frtime = GetTickCount();
	Update_Rect();

}

int MegaBullet::Update()
{
	float Dist = fabs(ObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - info.fX);
	if (true == dead || isdamaged || CCollisionMgr::Collision_TILE(this)
		|| Dist > 450) {
		ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<ChargeEffect>::Create(info.fX, info.fY, dir));
		return OBJ_DEAD;
	}
	switch (dir)
	{
	case DIR_LEFT:
		frameKey = L"CHARGE_BULLET_LEFT";
		info.fX -= speed;
		break;
	case DIR_RIGHT:
		frameKey = L"CHARGE_BULLET_RIGHT";
		info.fX += speed;
		break;
	}

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

int MegaBullet::Late_Update()
{
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(MONSTER));
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(OBSTACLE));
	//ÃÑ¾Ë»èÁ¦
	return 0;
}

void MegaBullet::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	HDC memDC = bmpmgr->Find_Image(frameKey);

	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX) ,
		int(rectinfo.top),
		128,
		96,
		memDC,
		frame.Start * 64,
		frame.Scean * 48,
		64,
		48,
		RGB(200, 0, 255));
}

void MegaBullet::Release()
{
}
