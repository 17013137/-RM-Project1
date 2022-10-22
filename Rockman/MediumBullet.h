#pragma once
#include "Obj.h"

class MediumBullet : public Obj
{
public:
	MediumBullet();
	virtual ~MediumBullet();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
};