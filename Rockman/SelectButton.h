#pragma once
#include "Obj.h"
#include "KeyMgr.h"
class SelectButton : public Obj
{
public:
	SelectButton();
	~SelectButton();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	void Key_input();

private:
	int id;

};

