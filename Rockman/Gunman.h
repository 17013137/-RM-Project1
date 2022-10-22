#pragma once
#include "Obj.h"

class Gunman : public Obj
{
public:
	Gunman();
	~Gunman();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

public:
	void Action_Change();
	void Gunman_Move();
	void Gunman_Attack();

protected:
	void TargetPlayer();
	Obj* player;
	ATTACKINFO attack;
	bool attack_rdy;
	int temp;
	DWORD timer;
};

