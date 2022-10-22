#include "stdafx.h"
#include "ST1Boss.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "BossBullet.h"
#include "SceneMgr.h"
#include "ExplosionEffect.h"
ST1Boss::ST1Boss()
{
	player = ObjMgr::Get_Instance()->Get_Player();
	attack_rdy = false;
	timer = 0;
	timer3 = 0;
	stat.damage = 10;
	stat.maxhp = 2000;
	stat.hp = 2000;
	temp = 0;
	cnt = 0;
	timer2 = 0;
	flagtimer2 = false;
	patern = false;
	paterntimer = 0;
	random = 0;
}


ST1Boss::~ST1Boss()
{
	Release();
}

void ST1Boss::Initialize()
{
	info.fX = 500.f;
	info.fY = 200.f;

	info.fcX = 350.f;
	info.fcY = 350.f;

	id = MONSTER;
	speed = 5.0f;
	dir = DIR_LEFT;
	state = IDLE;
	preState = APPEARANCE;

	bmpmgr->Insert_Bmp(L"../Image/03.Monster/ST3_Boss/Boss3.bmp", L"BIGHEAD");
	bmpmgr->Insert_Bmp(L"../Image/03.Monster/ST3_Boss/Laser.bmp", L"Laser");
	bmpmgr->Insert_Bmp(L"../Image/03.Monster/ST3_Boss/Boss3_bullet.bmp", L"HEAD_BULLET");
	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Explosion/explosion.bmp", L"EXPLOSION");

	frameKey = L"BIGHEAD";
	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 0;
	frame.frspeed = 100;
	frame.frtime = GetTickCount();

	srand(time(NULL));
	random = rand() % 2 + 1;
}

int ST1Boss::Update()
{

	if (true == dead) {
		if (timer3 == 0) {
			timer3 = GetTickCount();
			ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<ExplosionEffect>::Create(info.fX, info.fY));
			ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<ExplosionEffect>::Create(info.fX - 100, info.fY - 50));
			ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<ExplosionEffect>::Create(info.fX - 60, info.fY + 100));
			ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<ExplosionEffect>::Create(info.fX + 150, info.fY - 70));
			ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<ExplosionEffect>::Create(info.fX + 30, info.fY - 50));
		}
		if (timer3 + 3000 < GetTickCount()) {
			SceneMgr::Get_Instance()->SceneChange(ENDING);
			return OBJ_DEAD;
		}
		return OBJ_NOEVENT;
	}


	Boss_Patern();
	Move();
	Action_Change();

	Move_Frame();
	Update_Rect();

	return OBJ_NOEVENT;
}

int ST1Boss::Late_Update()
{
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(BULLET));
	return 0;
}

void ST1Boss::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();

	HDC memDC = bmpmgr->Find_Image(frameKey);
	//Rectangle(hdc, rectinfo.left + scrollX, rectinfo.top, rectinfo.right + scrollX, rectinfo.bottom);
	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX ),
		int(rectinfo.top ),
		350,
		350,
		memDC,
		frame.Start * 175,
		frame.Scean * 175,
		175,
		175,
		RGB(255, 0, 255));

}

void ST1Boss::Release()
{

}

void ST1Boss::Boss_Patern()
{
	if (temp == 3) {
		if (paterntimer == 0)
			paterntimer = GetTickCount();
		if (paterntimer + 3000 < GetTickCount()) {
			if (patern == false) patern = true;
			else patern = false;
			paterntimer = 0;
			temp = 0;
		}
		return;
	}

	if(!patern)
		temp = Attack();
	if (patern)
		temp = Shot();

}

int ST1Boss::Attack()
{
	float dist = fabsf(player->Get_Info().fX - info.fX);
	if (!attack2.attackcool) {	//재공격 시 쿨타임
		if (info.fX < 800) {
			info.fX += speed*2;
		}
		state = IDLE;
		if (attack2.attacktime + 3000 < GetTickCount()) {
			attack2.attackcool = true;
			attack2.attacktime = 0;
			return 3;
		}
		
		return 1;
	}

	if (!attack2.attacking && attack2.attackcool == true) {	// 플레이어가 접근했을경우
		attack_rdy = true;
		if (attack2.attacktime == 0)
			attack2.attacktime = GetTickCount();

	}

	if (attack_rdy == true) {
		state = ATTACK;
		if (attack2.attacktime + 500 < GetTickCount()) {
			attack2.attacking = true;
			attack_rdy = false;
			attack2.attacktime = 0;
			attack2.attacktime = GetTickCount();
		}
	}
	if (attack2.attacking == true) {
		info.fX -= 20.f;

		if (attack2.attacktime + 800 < GetTickCount()) {
			attack2.attacking = false;
			attack2.attackcool = false;
			attack2.attacktime = 0;
			attack2.attacktime = GetTickCount();
		}
	}

	return 1;
}

int ST1Boss::Shot()
{
	if (cnt > 5) {
		state = IDLE;
		if(timer2 == 0)
			timer2 = GetTickCount();
		if (timer2 + 3000 < GetTickCount()) {
			cnt = 0;
			timer2 = 0;
		}
		return 3;
	}

	if (!attack.attackcool) {	//보스 슛할때 쏘는 간격
		if (timer == 0)
			timer = GetTickCount();
		if (timer + 50 < GetTickCount()) {
			attack.attackcool = true;
			timer = 0;
		}

		return 2;
	}

	Obj* boomb = nullptr;
	if (!attack.attacking) {
		attack.attacking = true;
		if (attack.attacktime == 0) {
			cnt++;
			attack.attacktime = GetTickCount();
		}
	}
	if (attack.attacking) {
		state = ATTACK_READY;
		if (attack.attacktime + 1000 < GetTickCount()) {
			boomb = CAbstractFactory<BossBullet>::Create(info.fX-120, info.fY+100, dir);
			ObjMgr::Get_Instance()->Set_Objlist(MONSTER_BULLET, boomb);
			attack.attacktime = 0;
			attack.attacking = false;
			attack.attackcool = false;
		}
	}

	return 2;
}

void ST1Boss::Move()
{
	//if (!attack2.attacking || !attack.attacking)
	//	state = IDLE;

}

void ST1Boss::Action_Change()
{
	if (preState != state) {
		switch (state)
		{
		case IDLE:
			frame.Scean = 0;
			frame.Start = 0;
			frame.End = 0;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;

		case ATTACK: //돌진기
			frame.Scean = 0;
			frame.Start = 0;
			frame.End = 3;
			frame.frtime = GetTickCount();
			frame.frspeed = 50;
			break;

		case ATTACK_READY:
			frame.Scean = 1;
			frame.Start = 0;
			frame.End = 3;
			frame.frtime = GetTickCount();
			frame.frspeed = 50;
			break;
		}
		preState = state;
	}
}
