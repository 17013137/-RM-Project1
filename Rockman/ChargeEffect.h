#pragma once
#include "Obj.h"

class ChargeEffect : public Obj
{
public:
	ChargeEffect();
	~ChargeEffect();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

public:

private:
	Obj* bullet;
	DWORD timer;
};

