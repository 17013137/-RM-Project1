#include "stdafx.h"
#include "Player.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "MegaBullet.h"
#include "MediumBullet.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "SceneMgr.h"
#include "DashEffect.h"
#include "MiddleCharge.h"
#include "FullCharge.h"
#include "UIMgr.h"


Player::Player()
{
	pbullet = nullptr;
	isMove = false;
	isclimb = false;
	isjumpattack = false;
	scrollX = 0;
	timer = 0;
	victory = false;
	Eff = nullptr;
	Eff2 = nullptr;
	cheat = false;
}


Player::~Player()
{
	Release();
}

void Player::Initialize()
{

	info.fX = 500.f;
	info.fY = 300.f;
	info.fcX = 50.f;
	info.fcY = 110.f;

	stat.maxhp = 100;
	stat.hp = 100;
	stat.die = false;

	id = PLAYER;
	speed = 12.0f;
	power = 20.f;
	time = 0.f;
	dir = DIR_RIGHT;
	state = APPEARANCE;
	preState = IDLE;

	bmpmgr->Insert_Bmp(L"../Image/01.Player/x_left.bmp", L"PLAYER_LEFT");
	bmpmgr->Insert_Bmp(L"../Image/01.Player/x_right.bmp", L"PLAYER_RIGHT");
	bmpmgr->Insert_Bmp(L"../Image/02.Bullet/bullet_left.bmp", L"BULLET_LEFT");
	bmpmgr->Insert_Bmp(L"../Image/02.Bullet/bullet_right.bmp", L"BULLET_RIGHT");
	bmpmgr->Insert_Bmp(L"../Image/02.Bullet/charge_bullet_left.bmp", L"CHARGE_BULLET_LEFT");
	bmpmgr->Insert_Bmp(L"../Image/02.Bullet/charge_bullet_right.bmp", L"CHARGE_BULLET_RIGHT");
	bmpmgr->Insert_Bmp(L"../Image/02.Bullet/medium_bullet_left.bmp", L"MEDIUM_BULLET_LEFT");
	bmpmgr->Insert_Bmp(L"../Image/02.Bullet/medium_bullet_right.bmp", L"MEDIUM_BULLET_RIGHT");
	bmpmgr->Insert_Bmp(L"../Image/02.Bullet/medium_bullet_left.bmp", L"MEDIUM_BULLET_LEFT");
	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Player/dash_left.bmp", L"DASH_LEFT");
	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Player/dash_right.bmp", L"DASH_RIGHT");
	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Player/charge.bmp", L"CHARGE");
	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Player/full_charge.bmp", L"FULLCHARGE");
	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Player/full_charge11.bmp", L"FULLCHARGE11");


	frameKey = L"PLAYER_RIGHT";
	frame.Scean = 1;
	frame.Start = 0;
	frame.End = 8;
	frame.frspeed = 100;
	frame.frtime = GetTickCount();


}

int Player::Update()
{
	if (info.fX >= 9400)
		victory = true;

	if (victory) {
		SceneMgr::Get_Instance()->SceneChange(LOADING);
		//dead = true;
		victory = false;
	}
	if (true == dead)
		return OBJ_DEAD;

	Move_Frame();
	Update_Rect();
	Key_input();
	Jumping();
	Dash();
	Attack();
	ChargeAttack();
	Action_Change();

	return OBJ_NOEVENT;
}

int Player::Late_Update()
{
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(MONSTER));
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(OBSTACLE));
	CCollisionMgr::Collision_Obj(this, ObjMgr::Get_Instance()->Get_objlist(MONSTER_BULLET));
	if (isdamaged == true) { //피격시
		state = DAMAGED;
		if (dir == DIR_RIGHT)
			info.fX -= 1.f;
		else
			info.fX += 1.f;
		if (timer == 0)
			timer = GetTickCount();
		if (timer + 1000 < GetTickCount()) {
			isdamaged = false;
			super = true;
			timer = 0;
			timer = GetTickCount();
		}
	}
	Climing();
	OffSet();
	return OBJ_NOEVENT;
}

void Player::Render(HDC hdc)
{
	//Rectangle(hdc, rectinfo.left + scrollX, rectinfo.top, rectinfo.right + scrollX, rectinfo.bottom);
	//Ellipse(hdc, rectinfo.left + scrollX, rectinfo.top, rectinfo.right + scrollX, rectinfo.bottom);
	HDC memDC = bmpmgr->Find_Image(frameKey);
	scrollX = (int)ScrollMgr::Get_Instance()->Get_ScrollX();


	GdiTransparentBlt(hdc,
		int(rectinfo.left - info.fcX/2 + scrollX- 80),
		int(rectinfo.top - info.fcY/2-20),
		260,
		260,
		memDC,
		frame.Start * 260,
		frame.Scean * 260,
		260,
		260,
		RGB(200, 0, 255));


}

void Player::Release()
{

}

void Player::Key_input()
{
	float tempX = info.fX;
	if (isdamaged == true) { //피격시
		return;
	}

	if (timer + 1000 < GetTickCount()) { //피격 후 무적시간
		timer = 0;
		super = false;
	}

	if (state == APPEARANCE){ //등장씬
		return;
	}
	
	if (KeyMgr::Get_Instance()->Key_DOWN('C')) { //점프커맨드
		if (jump)
			return;
		jump = true;
		info.fY -= 3.f;
	}

	if (KeyMgr::Get_Instance()->Key_DOWN('T')) { //치트키
		cheat = true;
	}

	if (KeyMgr::Get_Instance()->Key_DOWN('X')) {
		if (attack.attacking == true)
			return;
		if (attack.attacktime == 0) {
			attack.attacktime = GetTickCount();
		}
		attack.attackcool = false;
		attack.attacking = true;
		attack.chargestart = true;
		if (cheat)
			Create_Bullet(CHARGE_BULLET);
		else
			Create_Bullet(NOMAL_BULLET);
	}
	if (KeyMgr::Get_Instance()->Key_Pressing('X')) {
		attack.chargetotal += 1.f;
		if (attack.chargetotal == 20.f) {
			Eff = CAbstractFactory<MiddleCharge>::Create(info.fX, info.fY, this);
			ObjMgr::Get_Instance()->Set_Objlist(EFFECT, Eff);
		}
		if (attack.chargetotal == 30.f) {
			Eff2 = CAbstractFactory<FullCharge>::Create(info.fX, info.fY, this);
			ObjMgr::Get_Instance()->Set_Objlist(EFFECT, Eff2);
		}
	}
	if (KeyMgr::Get_Instance()->Get_isdown() == true) { //X키 업
		if (Eff != nullptr) {
			Eff2->Set_Dead();
			Eff2->Release();
			Eff2 = nullptr;
			Eff->Set_Dead();
			Eff->Release();
			Eff = nullptr;
		}
		if (attack.chargelevel == 1) {
			Create_Bullet(MEDIUM_BULLET);
		}
		else if (attack.chargelevel == 2)
			Create_Bullet(CHARGE_BULLET);
		attack.chargestart = false;
		attack.chargeaction = true;
		attack.attackcool = false;
		attack.attacking = true;
		attack.chargetotal = 0;
		if (attack.chargetime == 0)
			attack.chargetime = GetTickCount();
		KeyMgr::Get_Instance()->isdown = false;
	}

	if (KeyMgr::Get_Instance()->Key_DOWN('Z') && dash.dashcool == true && jump == false) {
		if (dash.dashcool == false)
			return;
		ObjMgr::Get_Instance()->Set_Objlist(EFFECT, CAbstractFactory<DashEffect>::Create(info.fX, info.fY, this));
		dash.dashing = true;
		dash.dashcool = false;
		dash.dashY = info.fY;
		dash.dashtime = GetTickCount();

	}
	else if (GetAsyncKeyState(VK_LEFT) && dash.dashing == false) {
		dir = DIR_LEFT;
		info.fX -= speed;
		frameKey = L"PLAYER_LEFT";
		state = MOVE;
		isMove = true;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && dash.dashing == false) {
		dir = DIR_RIGHT;
		info.fX += speed;
		frameKey = L"PLAYER_RIGHT";
		state = MOVE;
		isMove = true;
	}
	else if (stat.hp < 50) {
		state = MORTAL;
		isMove = false;
	}
	else {
		state = IDLE;
		isMove = false;
	}
}

void Player::Action_Change()
{
	if (preState != state) {
		switch (state)
		{
		case IDLE:
			frame.Scean = 1;
			frame.Start = 0;
			frame.End = 8;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;

		case MORTAL:
			frame.Scean = 24;
			frame.Start = 0;
			frame.End = 5;
			frame.frtime = GetTickCount();
			frame.frspeed = 200;
			break;

		case APPEARANCE:
			frame.Scean = 0;
			frame.Start = 0;
			frame.End = 17;
			frame.frtime = GetTickCount();
			frame.frspeed = 75;
			break;

		case ATTACK:
			frame.Scean = 2;
			frame.Start = 0;
			frame.End = 7;
			frame.frtime = GetTickCount();
			frame.frspeed = 50;
			break;

		case CHARGE_ATTACK:
			frame.Scean = 3;
			frame.Start = 0;
			frame.End = 7;
			frame.frtime = GetTickCount();
			frame.frspeed = 50;
			break;

		case MOVE_ATTACK:
			frame.Scean = 5;
			frame.Start = (frame.Temp + 1) % 16 + 2;
			frame.End = 15;
			frame.frtime = frame.frtime;
			frame.frspeed = 50;
			break;

		case JUMP_ATTACKUP:
			frame.Scean = 11;
			frame.Start = 0;
			frame.End = 3;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;
		case JUMP_ATTACKDOWN:
			frame.Scean = 13;
			frame.Start = 0;
			frame.End = 3;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;

		case DASH_ATTACK:
			frame.Scean = 7;
			frame.Start = frame.Start;
			frame.End = 11;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;

		case MOVE:
			frame.Scean = 4;
			frame.Start = 5;
			frame.End = 15;
			frame.frtime = GetTickCount();
			frame.frspeed = 50;
			break;
		
		case DASH:
			frame.Scean = 6;
			frame.Start = 0;
			frame.End = 11;
			frame.frtime = GetTickCount();
			frame.frspeed = 50;
			break;

		case JUMPUP:
			frame.Scean = 10;
			frame.Start = 0;
			frame.End = 3;
			frame.frtime = GetTickCount();
			frame.frspeed = 70;
			break;

		case JUMPDOWN:
			frame.Scean = 12;
			frame.Start = 0;
			frame.End = 3;
			frame.frtime = GetTickCount();
			frame.frspeed = 60;
			break;

		case CLIMB:
			frame.Scean = 19;
			frame.Start = 0;
			frame.End = 2;
			frame.frtime = GetTickCount();
			frame.frspeed = 60;
			break;

		case CLIMB_ATTACK:
			frame.Scean = 20;
			frame.Start = 0;
			frame.End = 2;
			frame.frtime = GetTickCount();
			frame.frspeed = 60;
			break;

		case DAMAGED:
			frame.Scean = 23;
			frame.Start = 0;
			frame.End = 3;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;
		}
		preState = state;
	}
}

void Player::Jumping()
{
	float fY = 0.f;
	int col_tile = CCollisionMgr::Collision_TILE(this);
//	if (collison == true) {
//		jump = false;
//		attack.attacking = false;
//		isjumpattack = false;
//		time = 0.f;
//		dash.dashcool = true;
//
//		return;
//	}
	bool bLineCol = LineMgr::Get_Instance()->Collision_Line(&info.fX, &fY);

	if (jump == true) {
		if (col_tile == 1) {
			jump = false;
			attack.attacking = false;
			isjumpattack = false;
			time = 0.f;
			dash.dashcool = true;
		}
		if (bLineCol && (info.fY - 10 > fY)) {
			jump = false;
			attack.attacking = false;
			isjumpattack = false;
			info.fY = fY;
			time = 0.f;
			dash.dashcool = true;
		}

		if (attack.attacking == true || isjumpattack == true) {
			state = JUMP_ATTACKUP;
			isjumpattack = true;
		}
		else state = JUMPUP;

		//info.fY -= (power * time) - ((9.8f*time*time) / 2.f);
		//time += 0.1f;
		if (((9.8f * time * time) / 2.f) > (power * time)+10){
			if (dash.dashtime) {
				info.fY += 15.6f;
			}
			else
				info.fY += 12.8f;
			if (attack.attacking == true || isjumpattack == true)
				state = JUMP_ATTACKDOWN;
			else state = JUMPDOWN;
		}
		else {
			info.fY -= (power * time) - ((9.8f*time*time) / 2.f);
			time += 0.3f;
		}
		/*
		if (((9.8f * time * time) / 2.f) > (power * time)) {
			if (attack.attacking == true || isjumpattack == true)
				state = JUMP_ATTACKDOWN;
			else state = JUMPDOWN;
		}
		*/
	}
	else if (!bLineCol && jump == false && col_tile == 0) {
		info.fY += 9.8f;
		if (state == APPEARANCE)
			return;
		if (attack.attacking == true || isjumpattack == true) {
			state = JUMP_ATTACKDOWN;
		}
		else state = JUMPDOWN;
	}
	else if (bLineCol == true) {
		info.fY = fY;
	}
}

void Player::Dash()
{
	if (dash.dashing == true) {
		speed = 20.f;
		if (jump == false) {
			if (attack.attacking) {
				state = DASH_ATTACK;
			}
			else
				state = DASH;
		}
		
		if (dir == DIR_RIGHT)
			info.fX += speed;
		else
			info.fX -= speed;
		if (dash.dashtime + 500 < GetTickCount()) { //대쉬시간
			dash.dashing = false;
			dash.dashcool = true;
			speed = 12.f;
		}
	}
}

void Player::Attack()
{
	int col_tile = CCollisionMgr::Collision_TILE(this);
	if (attack.attacking) {
		
		if (jump == true || dash.dashing == true) {
			if (attack.attacktime + 100 < GetTickCount()) {
				attack.attacking = false;
				attack.attacktime = 0;
			}
			return;
		}
		if (isMove == false ) {
			state = ATTACK;
		}
		else if (isMove == true)
			state = MOVE_ATTACK;
		

		if (attack.attacktime + 200 < GetTickCount()) {
			attack.attacking = false;
			attack.attacktime = 0;
		}
	}

}

void Player::ChargeAttack()
{
	if (attack.chargestart == true) {
		if (attack.chargetotal > 40.f) {
			attack.chargelevel = 2;
		}
		else if (attack.chargetotal > 20) {
			attack.chargelevel = 1;
		}
	}
	else {
		if (attack.chargelevel == 2)
				state = CHARGE_ATTACK;

		if (attack.chargetime + 200 < GetTickCount()) {
			attack.chargetime = 0;
			attack.chargelevel = 0;
			attack.chargetotal = 0;
			attack.chargeaction = false;
		}
	}
	
}

void Player::OffSet()
{
	int offset = WINCX / 2;
	scrollX = (int)ScrollMgr::Get_Instance()->Get_ScrollX();

	
	if (offset > info.fX + scrollX - 20) {
		ScrollMgr::Get_Instance()->Set_ScrollX(speed);
	}
	
	if (offset < info.fX + scrollX) {
		ScrollMgr::Get_Instance()->Set_ScrollX(-speed);
	}
	

}

void Player::Climing()
{
	if (isclimb) {
		if (attack.attacking) {
			state = CLIMB_ATTACK;
		}
		else
			state = CLIMB;

		info.fY += 3.0f;

	}
}

void Player::Create_Bullet(BULLETID bulletid)
{
	scrollX = (int)ScrollMgr::Get_Instance()->Get_ScrollX();
	Obj* bullet = nullptr;
	if (state == DASH || state == DASH_ATTACK) {
		if(bulletid == NOMAL_BULLET)
			bullet = CAbstractFactory<Bullet>::Create(info.fX, info.fY, dir);
		else if(bulletid == MEDIUM_BULLET)
			bullet = CAbstractFactory<MediumBullet>::Create(info.fX, info.fY, dir);
		else {
			bullet = CAbstractFactory<MegaBullet>::Create(info.fX, info.fY, dir);
		}
	}
	else if (state == JUMPDOWN || state == JUMPUP || state == JUMP_ATTACKUP || state == JUMP_ATTACKDOWN) {
		if (bulletid == NOMAL_BULLET)
			bullet = CAbstractFactory<Bullet>::Create(info.fX, info.fY+10, dir);
		else if (bulletid == MEDIUM_BULLET)
			bullet = CAbstractFactory<MediumBullet>::Create(info.fX, info.fY+10, dir);
		else
			bullet = CAbstractFactory<MegaBullet>::Create(info.fX, info.fY+10, dir);
	}
	else {
		if (bulletid == NOMAL_BULLET)
			bullet = CAbstractFactory<Bullet>::Create(info.fX, info.fY-25, dir);
		else if (bulletid == MEDIUM_BULLET)
			bullet = CAbstractFactory<MediumBullet>::Create(info.fX, info.fY-25, dir);
		else
			bullet = CAbstractFactory<MegaBullet>::Create(info.fX, info.fY-25, dir);
	}

	ObjMgr::Get_Instance()->Set_Objlist(BULLET, bullet);
}