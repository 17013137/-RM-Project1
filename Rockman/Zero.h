#pragma once
#include "Obj.h"
class Zero : public Obj
{
public:
	Zero();
	~Zero();

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
	void OffSet();
	void Climing();

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
};

