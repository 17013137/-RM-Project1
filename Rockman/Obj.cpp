#include "stdafx.h"
#include "Obj.h"


Obj::Obj()
{
	bmpmgr = BmpMgr::Get_Instance();
	dead = false;
	frameKey = nullptr;
	jump = false;
	collison = false;
	isdamaged = false;
	super = false;
	target = nullptr;
}


Obj::~Obj()
{
}

void Obj::Update_Rect()
{
	rectinfo.left = LONG(info.fX - info.fcX/2);
	rectinfo.top = LONG(info.fY - info.fcY/2 );
	rectinfo.right = LONG(info.fX + info.fcX/2);
	rectinfo.bottom = LONG(info.fY + info.fcY/2);
}

void Obj::Move_Frame()
{
	if (frame.frtime + frame.frspeed < GetTickCount()) {
		if (state == APPEARANCE) {
			++frame.Start;
			frame.frtime = GetTickCount();

			if (frame.Start >= frame.End) state = IDLE;
		}
		else if (state == MOVE) {
			++frame.Start;
			frame.Temp = frame.Start;
			frame.frtime = GetTickCount();
			if (frame.Start > frame.End) frame.Start = 2;
		}
		else if(state == JUMPUP || state == JUMPDOWN ||
			state == ATTACK || state == JUMP_ATTACKUP || state == JUMP_ATTACKDOWN ||
			state == CLIMB || state == CLIMB_ATTACK || state == ATTACK_READY ||
			state == ATTACK_END){
			++frame.Start;
			frame.frtime = GetTickCount();
			if (frame.Start >= frame.End)
				frame.Start = frame.End;
		}
		else {
			++frame.Start;
			frame.frtime = GetTickCount();

			if (frame.Start > frame.End) frame.Start = 0;
		}
	}
}

void Obj::Set_Pos(float _fX, float _fY)
{
	info.fX = _fX;
	info.fY = _fY;

}


