#pragma once
#include "Obj.h"
class Monster_Boomb : public Obj
{
public:
	Monster_Boomb();
	~Monster_Boomb();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

