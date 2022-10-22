#include "stdafx.h"
#include "Boss_obs.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "Boss_Attack.h"
Boss_obs::Boss_obs()
{
	player = ObjMgr::Get_Instance()->Get_Player();
	timer = 0;
	stat.damage = 10;
	stat.maxhp = 300;
	stat.hp = 300;
	temp = 0;
	target = false;
}


Boss_obs::~Boss_obs()
{
	Release();
}

void Boss_obs::Initialize()
{


	info.fcX = 50.f;
	info.fcY = 50.f;

	id = MONSTER;
	speed = 5.f;
	dir = DIR_LEFT;
	state = IDLE;
	preState = APPEARANCE;

	bmpmgr->Insert_Bmp(L"../Image/03.Monster/ST1_Boss/Eregion_left.bmp", L"EREGION_RIGHT");
	bmpmgr->Insert_Bmp(L"../Image/03.Monster/ST1_Boss/Eregion_right.bmp", L"EREGION_LEFT");
	bmpmgr->Insert_Bmp(L"../Image/03.Monster/ST1_Boss/Eregion_RiseAttk.bmp", L"EREGION_RISEATTK");
	bmpmgr->Insert_Bmp(L"../Image/03.Monster/ST1_Boss/Eregion_fire.bmp", L"EREGION_FIRE");
	bmpmgr->Insert_Bmp(L"../Image/03.Monster/ST1_Boss/Eregion_firedown.bmp", L"EREGION_FIREDOWN");
	bmpmgr->Insert_Bmp(L"../Image/03.Monster/ST1_Boss/Eregion_Upper.bmp", L"EREGION_UPPER");

	frameKey = L"EREGION_LEFT";
	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 3;
	frame.frspeed = 100;
	frame.frtime = GetTickCount();
}

int Boss_obs::Update()
{
	

	if (true == dead)
		return OBJ_DEAD;

	Monster_Attack();
	Monster_Move();
	Action_Change();

	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

int Boss_obs::Late_Update()
{
	TargetPlayer();
	return 0;
}

void Boss_obs::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	HDC memDC = bmpmgr->Find_Image(frameKey);
	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX - 375),
		int(rectinfo.top - 300),
		800,
		800,
		memDC,
		frame.Start * 400,
		frame.Scean * 400,
		400,
		400,
		RGB(255, 0, 255));

}

void Boss_obs::Monster_Attack()
{
	if (!attack.attackcool) { // 스킬 쿨일경우 넘기기
		if (timer + 1000 < GetTickCount()) {
			attack.attackcool = true;
		}

		return;
	}

	float Dist = fabsf(player->Get_Info().fX - info.fX);
	Obj* punch = nullptr;
	if (Dist <= 100 && !attack.attacking) {
		attack.attacking = true;
		if (attack.attacktime == 0) {
			attack.attacktime = GetTickCount();

		}
	}

	if (attack.attacking) {
		state = ATTACK;
		if (attack.attacktime + 1000 < GetTickCount()) {
			if(dir == DIR_LEFT)
				punch = CAbstractFactory<Boss_Attack>::Create(info.fX - 150, info.fY + 300, dir);
			else
				punch = CAbstractFactory<Boss_Attack>::Create(info.fX + 150, info.fY + 300, dir);
			ObjMgr::Get_Instance()->Set_Objlist(MONSTER, punch);
			attack.attacking = false;
			attack.attackcool = false;
			attack.attacktime = 0;
			timer = GetTickCount();
		}
	}

}

void Boss_obs::Monster_Move()
{
	
	float Dist = fabsf(player->Get_Info().fX - info.fX);

	if (!target)
		return;

	if (info.fX > 8300) {
		if(Dist > 500)
			dead = true;
		return;
	}

	if (!attack.attacking) {
		state = IDLE;
		if (dir == DIR_LEFT && Dist > 100) {
			info.fX -= speed;
		}
		else if (dir == DIR_RIGHT) {
			if (Dist > 600)
				info.fX += 15;
			else info.fX += speed;
		}
	}

}

void Boss_obs::TargetPlayer()
{
	float Dist = fabsf(player->Get_Info().fX - info.fX);

	if (Dist < 500)
		target = true;

	if (attack.attacking)
		return;

	if (player->Get_Info().fX+50 > info.fX) {
		dir = DIR_RIGHT;
		frameKey = L"EREGION_RIGHT";
	}
	else {
		dir = DIR_LEFT;
		frameKey = L"EREGION_LEFT";
	}
}

void Boss_obs::Action_Change()
{
	if (preState != state) {
		switch (state)
		{
		case ATTACK:
			frame.Scean = 1;
			frame.Start = 0;
			frame.End = 3;
			frame.frtime = GetTickCount();
			frame.frspeed = 700;
			break;

		case IDLE:
			frame.Scean = 0;
			frame.Start = 0;
			frame.End = 3;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;

		}
		preState = state;
	}
}

void Boss_obs::Release()
{
}