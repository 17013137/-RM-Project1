#include "stdafx.h"
#include "Monster.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "ExplosionEffect.h"

//rolling 150 X 150
Monster::Monster()
{
	player = ObjMgr::Get_Instance()->Get_Player();
	attack_rdy = false;
	time = 0;
	stat.damage = 10;
	stat.maxhp = 50;
	stat.hp = 50;
	temp = 0;
}


Monster::~Monster()
{
	Release();
}

void Monster::Initialize()
{
	info.fX = 750.f;
	info.fY = 400.f;

	info.fcX = 80.f;
	info.fcY = 80.f;

	id = MONSTER;
	speed = 3.0f;
	dir = DIR_LEFT;
	state = IDLE;
	preState = APPEARANCE;

	bmpmgr->Insert_Bmp(L"../Image/03.Monster/Rolling/Rolling_left.bmp", L"ROLLING_RIGHT");
	bmpmgr->Insert_Bmp(L"../Image/03.Monster/Rolling/Rolling_right.bmp", L"ROLLING_LEFT");
	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Explosion/explosion.bmp", L"EXPLOSION");

	frameKey = L"ROLLING_LEFT";
	frame.Scean = 1;
	frame.Start = 0;
	frame.End = 5;
	frame.frspeed = 100;
	frame.frtime = GetTickCount();
}

int Monster::Update()
{
	if (true == dead) {
		ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<ExplosionEffect>::Create(info.fX, info.fY));
		return OBJ_DEAD;
	}
	Monster_Attack();
	Monster_Move();
	Action_Change();


	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

int Monster::Late_Update()
{
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(BULLET));
	if (attack.attacking == true)
		isdamaged = false;
	TargetPlayer();
	return 0;
}

void Monster::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	HDC memDC = bmpmgr->Find_Image(frameKey);
	//Ellipse(hdc, rectinfo.left + scrollX, rectinfo.top, rectinfo.right + scrollX, rectinfo.bottom);
	GdiTransparentBlt(hdc,
		int(rectinfo.left - 35 + scrollX),
		int(rectinfo.top) - 35,
		150,
		150,
		memDC,
		frame.Start * 150,
		frame.Scean * 150,
		150,
		150,
		RGB(200, 0, 255));

}

void Monster::Monster_Move()
{
	int col_tile = CCollisionMgr::Collision_TILE(this);
	if (col_tile != 1) {
		info.fY += 9.8f;
	}


}

void Monster::Monster_Attack()
{
	float dist = fabsf(player->Get_Info().fX - info.fX);
	if (!attack.attackcool) {	//재공격 시 쿨타임
		state = ATTACK_END;
		if (attack.attacktime + 2000 < GetTickCount()) {
			attack.attackcool = true;
			attack.attacktime = 0;
		}

		return;
	}
	
	if (dist < 300 && !attack.attacking && attack.attackcool == true) {	// 플레이어가 접근했을경우
		attack_rdy = true;
		if(attack.attacktime == 0)
			attack.attacktime = GetTickCount();
	}

	if (attack_rdy == true) {
		state = ATTACK_READY;
		if (attack.attacktime + 1000 < GetTickCount()) {
			attack.attacking = true;
			attack_rdy = false;
			attack.attacktime = 0;
			attack.attacktime = GetTickCount();
		}
	}
	if (attack.attacking == true) {
		state = ATTACK;
		temp = stat.hp;
		stat.hp = 110;
		if (dir == DIR_LEFT) {
			info.fX -= 12.f;
		}
		else {
			info.fX += 12.f;
		}
		if (attack.attacktime + 500 == GetTickCount())
			stat.hp = temp;

		if (attack.attacktime + 1000 < GetTickCount()) {
			attack.attacking = false;
			attack.attackcool = false;
			attack.attacktime = 0;
			attack.attacktime = GetTickCount();
		}
	}


}


void Monster::Release()
{
}

void Monster::Action_Change()
{
	if (preState != state) {
		switch (state)
		{
		case ATTACK:
			frame.Scean = 0;
			frame.Start = 0;
			frame.End = 6;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;

		case ATTACK_END:
			frame.Scean = 1;
			frame.Start = 0;
			frame.End = 5;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;

		case IDLE:
			frame.Scean = 2;
			frame.Start = 0;
			frame.End = 2;
			frame.frtime = GetTickCount();
			frame.frspeed = 300;
			break;

		case ROTATE:
			frame.Scean = 3;
			frame.Start = 0;
			frame.End = 3;
			frame.frtime = GetTickCount();
			frame.frspeed = 50;
			break;

		case ATTACK_READY:
			frame.Scean = 4;
			frame.Start = 0;
			frame.End = 6;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;

		}
		preState = state;
	}
}

void Monster::TargetPlayer()
{
	if (attack.attacking || attack.attackcool)
		return;

	if (player->Get_Info().fX > info.fX) {
		dir = DIR_RIGHT;
		frameKey = L"ROLLING_RIGHT";
	}
	else {
		dir = DIR_LEFT;
		frameKey = L"ROLLING_LEFT";
	}
	//if (fabsf(player->Get_Info().fX - info.fX) < 400) {
	//
	//}
}
