#pragma once
#include "Obj.h"

class Monster : public Obj
{
public:
	Monster();
	~Monster();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

public:
	void Action_Change();
	void Monster_Move();
	void Monster_Attack();

protected:
	void TargetPlayer();
	Obj* player;
	ATTACKINFO attack;
	bool attack_rdy;
	int temp;
	DWORD time;
};

