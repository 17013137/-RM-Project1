#include "stdafx.h"
#include "MapObj.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "ExplosionEffect.h"

MapObj::MapObj()
{
	stat.maxhp = 1; //장애물 체력
	stat.hp = 1;
	stat.damage = 50;
	info.fX = 0;
	info.fY = 0;
}


MapObj::~MapObj()
{
	Release();
}

void MapObj::Initialize()
{
	info.fcX = 100.f;
	info.fcY = 600.f;

	id = OBSTACLE;
	speed = 0;
	
	bmpmgr->Insert_Bmp(L"../Image/09.MapObject/ClosedDoor.bmp", L"CLOSED_DOOR");

	frameKey = L"CLOSED_DOOR";
}

int MapObj::Update()
{
	if (dead) {
		ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<ExplosionEffect>::Create(info.fX-20, info.fY));
		ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<ExplosionEffect>::Create(info.fX-20, info.fY-100));
		ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<ExplosionEffect>::Create(info.fX-20, info.fY-200));
		return OBJ_DEAD;
	}
	Update_Rect();
	return OBJ_NOEVENT;
}

int MapObj::Late_Update()
{
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(BULLET));
	return 0;
}

void MapObj::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	HDC memDC = bmpmgr->Find_Image(frameKey);

	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX - 75),
		int(rectinfo.top - 100),
		200,
		600,
		memDC,
		0,
		0,
		200,
		600,
		RGB(255, 0, 255));
}

void MapObj::Release()
{
}
