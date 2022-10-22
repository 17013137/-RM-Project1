#pragma once
#include "Obj.h"

class ST1Boss : public Obj
{
public:
	ST1Boss();
	~ST1Boss();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

public:
	int Attack();
	int Shot();
	void Move();
	void Action_Change();
	void Boss_Patern();

private:
	Obj* player;
	ATTACKINFO attack;
	ATTACKINFO attack2;
	bool attack_rdy;
	int cnt;
	int temp;
	DWORD timer;
	DWORD timer2;
	DWORD timer3;
	bool flagtimer2;
	bool patern;
	DWORD paterntimer;
	int random;
};

