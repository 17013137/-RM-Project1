#pragma once

typedef struct STAT {
	int maxhp;
	int hp;
	int damage;
	bool die;
	STAT()
		:maxhp(0), hp(0), damage(0), die(false){}
	STAT(int _maxhp, int _attack) {
		maxhp = _maxhp;
		hp = _maxhp;
		damage = _attack;
		die = false;
	}
}STAT;

typedef struct INFO
{
	float fX;
	float fY;
	float fcX;
	float fcY;


}INFO;

typedef struct FRAME {
	int Start;
	int End;
	int Scean;
	int Temp;

	DWORD frspeed;
	DWORD frtime;
}FRAME;

typedef struct DashInfo {
	bool dashing;
	bool dashcool;
	DWORD dashtime;
	float dashY;

	DashInfo(){
		dashing = false;
		dashtime = 0;
		dashY = 0.f;
		dashcool = true;
	}
}DASHINFO;

typedef struct AttackInfo {
	bool attacking;
	bool attackcool;
	DWORD attacktime;
	bool chargestart;
	float chargetotal;
	DWORD chargetime;
	int chargelevel;
	bool chargeaction;
	AttackInfo() {
		attacking = false;
		attackcool = true;
		attacktime = 0;
		chargestart = false;
		chargetime = 0;
		chargelevel = 0;
		chargeaction = false;
		chargetotal = 0;
	}
}ATTACKINFO;

typedef struct tagLinePos
{
	float		fX;
	float		fY;

	tagLinePos() { ZeroMemory(this, sizeof(tagLinePos)); }
	tagLinePos(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOS;


typedef struct tagLineInfo
{
	LINEPOS		tLeftPos;
	LINEPOS		tRightPos;

	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOS& tLeft, LINEPOS& tRight)
		: tLeftPos(tLeft), tRightPos(tRight) {}

}LINEINFO;

