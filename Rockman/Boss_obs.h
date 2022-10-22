#pragma once
#include "Obj.h"

class Boss_obs : public Obj
{
public:
	Boss_obs();
	~Boss_obs();

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

private:
	void TargetPlayer();
	Obj* player;
	ATTACKINFO attack;
	bool target;
	int temp;
	DWORD timer;
};

