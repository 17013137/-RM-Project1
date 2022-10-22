#include "stdafx.h"
#include "Boss_Attack.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"

Boss_Attack::Boss_Attack()
{
	id = MONSTER;
	dir = DIR_LEFT;
	stat.damage = 10;
	stat.maxhp = 10;
	stat.hp = 10;
	timer = 0;
	temp = 0;
}


Boss_Attack::~Boss_Attack()
{
	Release();
}


void Boss_Attack::Initialize()
{
	info.fcX = 144.f;
	info.fcY = 206.f;
	frameKey = L"EREGION_FIREDOWN";
	speed = 1.f;
	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 3;
	frame.frspeed = 200;
	frame.frtime = GetTickCount();
	Update_Rect();
	timer = GetTickCount();

}

int Boss_Attack::Update()
{
	if (timer + 500 < GetTickCount())
		dead = true;
	//float Dist = fabs(ObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - info.fX);
	if (true == dead) {

		return OBJ_DEAD;
	}
	
	if (timer%2 == 0) {
		ScrollMgr::Get_Instance()->Set_ScrollX(10.f);

	}
	else {
		ScrollMgr::Get_Instance()->Set_ScrollX(-10.f);

	}

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

int Boss_Attack::Late_Update()
{
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(PLAYER));
	return 0;
}

void Boss_Attack::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	//Rectangle(hdc, rectinfo.left + scrollX, rectinfo.top, rectinfo.right + scrollX, rectinfo.bottom);
	HDC memDC = bmpmgr->Find_Image(frameKey);
	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX),
		int(rectinfo.top),
		144,
		206,
		memDC,
		frame.Start * 36,
		frame.Scean * 54,
		36,
		54,
		RGB(255, 0, 255));

}

void Boss_Attack::Release()
{
}
