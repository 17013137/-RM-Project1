#pragma once
#include "Obj.h"

class MegaBullet : public Obj
{
public:
	MegaBullet();
	virtual ~MegaBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
};