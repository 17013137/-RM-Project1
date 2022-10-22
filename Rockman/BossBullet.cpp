#include "stdafx.h"
#include "BossBullet.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"

BossBullet::BossBullet()
{
	id = MONSTER_BULLET;
	dir = DIR_LEFT;
	stat.damage = 10;
	stat.maxhp = 10;
	stat.hp = 10;
}


BossBullet::~BossBullet()
{
	Release();
}

void BossBullet::Initialize()
{
	info.fcX = 72.f;
	info.fcY = 72.f;
	frameKey = L"HEAD_BULLET";
	speed = 15.f;
	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 3;
	frame.frspeed = 50;
	frame.frtime = GetTickCount();
	Update_Rect();

	Obj* m_pTarget = ObjMgr::Get_Instance()->Get_Player();

	if (m_pTarget)
	{
		float	fWidth = m_pTarget->Get_Info().fX - info.fX;
		float	fHeight = m_pTarget->Get_Info().fY - info.fY;

		float	fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

		float	fRadian = atan2f(fHeight, fWidth);

		angle = fRadian * (180.f / PI);
		if (m_pTarget->Get_Info().fY > info.fY)
			angle *= -1.f;
	}
}

int BossBullet::Update()
{
	float Dist = fabs(ObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - info.fX);
	if (true == dead || isdamaged || CCollisionMgr::Collision_TILE(this)) {
		isdamaged = false;
		return OBJ_DEAD;
	}

	
	info.fX += speed * cosf(angle * (PI/180.f));
	info.fY -= speed * sinf(-angle * (PI / 180.f));



	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

int BossBullet::Late_Update()
{
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(PLAYER));
	return 0;
}

void BossBullet::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	HDC memDC = bmpmgr->Find_Image(frameKey);
	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX -36),
		int(rectinfo.top -36),
		144,
		144,
		memDC,
		frame.Start * 36,
		frame.Scean * 36,
		36,
		36,
		RGB(255, 0, 255));
}

void BossBullet::Release()
{
}
