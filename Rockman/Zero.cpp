#include "stdafx.h"
#include "Zero.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "TileMgr.h"
#include "SceneMgr.h"
#include "DashEffect.h"
#include "UIMgr.h"
#include "AbstractFactory.h"
//175 175
Zero::Zero()
{
	isMove = false;
	isclimb = false;
	isjumpattack = false;
	scrollX = 0;

}


Zero::~Zero()
{
	Release();
}

void Zero::Initialize()
{
	info.fX = 100.f;
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

	bmpmgr->Insert_Bmp(L"../Image/01.Player/Zero_left.bmp", L"ZERO_LEFT");
	bmpmgr->Insert_Bmp(L"../Image/01.Player/Zero_right.bmp", L"ZERO_RIGHT");
	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Player/dash_left.bmp", L"DASH_LEFT");
	bmpmgr->Insert_Bmp(L"../Image/07.Effect/Player/dash_right.bmp", L"DASH_RIGHT");

	frameKey = L"PLAYER_RIGHT";
	frame.Scean = 2;
	frame.Start = 0;
	frame.End = 5;
	frame.frspeed = 100;
	frame.frtime = GetTickCount();
}

int Zero::Update()
{
	if (info.fX >= 9400)
		victory = true;

	if (victory) {
		SceneMgr::Get_Instance()->SceneChange(LOADING);
		//dead = true;
		victory = false;
	}

	if (true == dead) {
		SceneMgr::Get_Instance()->SceneChange(MENU);
		return OBJ_DEAD;
	}

	Move_Frame();
	Update_Rect();
	Key_input();
	Jumping();
	Dash();
	Attack();

	return OBJ_NOEVENT;
}

int Zero::Late_Update()
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

	OffSet();
	return OBJ_NOEVENT;
}

void Zero::Render(HDC hdc)
{
	HDC memDC = bmpmgr->Find_Image(frameKey);
	scrollX = (int)ScrollMgr::Get_Instance()->Get_ScrollX();
	Rectangle(hdc, rectinfo.left + scrollX, rectinfo.top, rectinfo.right + scrollX, rectinfo.bottom);

	GdiTransparentBlt(hdc,
		int(rectinfo.left +scrollX),
		int(rectinfo.top),
		260,
		260,
		memDC,
		frame.Start * 150,
		frame.Scean * 150,
		150,
		150,
		RGB(200, 0, 255));

}

void Zero::Release()
{
}

void Zero::Action_Change()
{
	if (preState != state) {
		switch (state)
		{
		case IDLE:
			frame.Scean = 2;
			frame.Start = 0;
			frame.End = 5;
			frame.frtime = GetTickCount();
			frame.frspeed = 100;
			break;

		case MORTAL:
			frame.Scean = 24;
			frame.Start = 0;
			frame.End = 3;
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

void Zero::Key_input()
{
	if (isdamaged == true) { //피격시
		return;
	}

	if (timer + 1000 < GetTickCount()) { //피격 후 무적시간
		timer = 0;
		super = false;
	}

	if (state == APPEARANCE) { //등장씬
		return;
	}

	if (KeyMgr::Get_Instance()->Key_DOWN('C')) { //점프커맨드
		if (jump)
			return;
		jump = true;
		info.fY -= 3.f;
	}

	if (KeyMgr::Get_Instance()->Key_DOWN('X')) { //공격
		
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

void Zero::Jumping()
{
}

void Zero::Dash()
{
}

void Zero::Attack()
{
}

void Zero::OffSet()
{
}

void Zero::Climing()
{
}
