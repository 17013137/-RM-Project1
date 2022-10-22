#pragma once
#include "Obj.h"

class Boss_Attack : public Obj
{
public:
	Boss_Attack();
	~Boss_Attack();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	DWORD timer;
	float temp;
};

