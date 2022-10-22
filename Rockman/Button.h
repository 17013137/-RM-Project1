#pragma once
#include "Obj.h"

class Button : public Obj
{
public:
	Button();
	~Button();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int id;

};

