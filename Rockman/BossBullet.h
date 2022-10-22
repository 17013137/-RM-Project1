#pragma once
#include "Monster_Boomb.h"

class BossBullet : public Monster_Boomb
{
public:
	BossBullet();
	~BossBullet();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	float angle;
};

