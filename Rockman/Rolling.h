#pragma once
#include "Obj.h"

class Rolling : public Obj
{
public:
	Rolling();
	~Rolling();

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

	DWORD time;
	int temp;
};

