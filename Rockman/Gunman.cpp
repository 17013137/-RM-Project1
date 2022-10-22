#include "stdafx.h"
#include "Gunman.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "Monster_Boomb.h"
#include "AbstractFactory.h"
#include "ExplosionEffect.h"

//rolling 150 X 150
Gunman::Gunman()
{
	player = ObjMgr::Get_Instance()->Get_Player();
	attack_rdy = false;
	timer = 0;
	stat.damage = 10;
	stat.maxhp = 50;
	stat.hp = 50;
	temp = 0;
}


Gunman::~Gunman()
{
	Release();
}

void Gunman::Initialize()
{
	info.fX = 100.f;
	info.fY = 400.f;

	info.fcX = 80.f;
	info.fcY = 100.f;

	id = MONSTER;
	speed = 1.0f;
	dir = DIR_LEFT;
	state = IDLE;
	preState = APPEARANCE;

	bmpmgr->Insert_Bmp(L"../Image/03.Monster/Gunman/gunman_left.bmp", L"GUNMAN_RIGHT");
	bmpmgr->Insert_Bmp(L"../Image/03.Monster/Gunman/gunman_right.bmp", L"GUNMAN_LEFT");
	bmpmgr->Insert_Bmp(L"../Image/03.Monster/Gunman/gunman_bullet.bmp", L"GUNMAN_BULLET");
	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Explosion/explosion.bmp", L"EXPLOSION");

	frameKey = L"GUNMAN_LEFT";
	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 7;
	frame.frspeed = 100;
	frame.frtime = GetTickCount();
}

int Gunman::Update()
{
	if (true == dead) {
		ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<ExplosionEffect>::Create(info.fX, info.fY));
		return OBJ_DEAD;
	}
	Gunman_Attack();
	Gunman_Move();
	Action_Change();


	Move_Frame();
	Update_Rect();
	return OBJ_NOEVENT;
}

int Gunman::Late_Update()
{
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(BULLET));
	TargetPlayer();
	return 0;
}

void Gunman::Render(HDC hdc)
{
	float scrollX = ScrollMgr::Get_Instance()->Get_ScrollX();
	HDC memDC = bmpmgr->Find_Image(frameKey);
	//Ellipse(hdc, rectinfo.left + scrollX, rectinfo.top, rectinfo.right + scrollX, rectinfo.bottom);
	GdiTransparentBlt(hdc,
		int(rectinfo.left + scrollX - 50),
		int(rectinfo.top - 60),
		200,
		200,
		memDC,
		frame.Start * 170,
		frame.Scean * 170,
		170,
		170,
		RGB(200, 0, 255));

}

void Gunman::Gunman_Move()  //건맨 무브
{
	float Dist = fabsf(player->Get_Info().fX - info.fX);
	int col_tile = CCollisionMgr::Collision_TILE(this);
	if (col_tile != 1) {
		info.fY += 9.8f;
	}

	if (!attack.attacking) {
		state = IDLE;
		if (Dist < 200) { //플레이어랑 가까우면 비비기
			if (dir == DIR_LEFT) {
				info.fX -= speed;
				state = MOVE;
			}
			else if (dir == DIR_RIGHT) {
				info.fX += speed;
				state = MOVE;
			}
		}
	}
}

void Gunman::Gunman_Attack()  //건맨 공격
{
	if (!attack.attackcool) { // 스킬 쿨일경우 넘기기
		if (timer + 5000 < GetTickCount()) {
			attack.attackcool = true;
		}

		return;
	}


	float Dist = fabsf(player->Get_Info().fX - info.fX);
	Obj* boomb = nullptr;
	if (Dist <= 600 && !attack.attacking) {
		attack.attacking = true;
		if (attack.attacktime == 0) {
			attack.attacktime = GetTickCount();

		}
	}
	if (attack.attacking) {
		state = APPEARANCE;
		if (attack.attacktime + 500 < GetTickCount()) {
			boomb = CAbstractFactory<Monster_Boomb>::Create(info.fX, info.fY, dir);
			ObjMgr::Get_Instance()->Set_Objlist(MONSTER_BULLET, boomb);
			attack.attacking = false;
			attack.attackcool = false;
			attack.attacktime = 0;
			timer = GetTickCount();
		}
	}
	
}


void Gunman::Release()
{
}

void Gunman::Action_Change()
{
	if (preState != state) {
		switch (state)
		{
		case ATTACK: //총알쏘기
			frame.Scean = 2;
			frame.Start = 0;
			frame.End = 3;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;

		case APPEARANCE: //폭탄던지기
			frame.Scean = 3;
			frame.Start = 0;
			frame.End = 6;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;

		case MOVE:
			frame.Scean = 1;
			frame.Start = 0;
			frame.End = 6;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;

		case IDLE:
			frame.Scean = 0;
			frame.Start = 0;
			frame.End = 7;
			frame.frtime = GetTickCount();
			frame.frspeed = 300;
			break;

		}
		preState = state;
	}
}

void Gunman::TargetPlayer()
{

	if (player->Get_Info().fX > info.fX) {
		dir = DIR_RIGHT;
		frameKey = L"GUNMAN_RIGHT";
	}
	else {
		dir = DIR_LEFT;
		frameKey = L"GUNMAN_LEFT";
	}

}
