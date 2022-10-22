#pragma once
#include "Obj.h"
#include "AbstractFactory.h"
class Player final : public Obj
{
public:
	Player();
	~Player();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	void Action_Change();
	void Key_input();
	void Jumping();
	void Dash();
	void Attack();
	void ChargeAttack();
	void OffSet();
	void Climing();

	void Create_Bullet(BULLETID bulletid);

private:
	list<Obj*>*	pbullet;

private:
	float power;
	float time;
	DWORD timer;

	bool victory;

	DASHINFO dash;
	ATTACKINFO attack;
	bool isMove;
	bool isclimb;
	bool isjumpattack;
	float prevY;

	int scrollX;
	Obj* Eff;
	Obj* Eff2;
	bool cheat;
};