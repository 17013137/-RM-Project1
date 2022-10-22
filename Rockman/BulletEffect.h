#pragma once
#include "Obj.h"

class BulletEffect : public Obj
{
public:
	BulletEffect();
	~BulletEffect();

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

