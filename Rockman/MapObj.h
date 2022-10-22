#pragma once
#include "Obj.h"

class MapObj : public Obj
{
public:
	MapObj();
	~MapObj();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

protected:
	Obj* player;
	ATTACKINFO attack;
	DWORD time;
};

