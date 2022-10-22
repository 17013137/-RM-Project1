#pragma once
#include "Scene.h"
#include "SelectButton.h"
class Menu : public Scene
{
public:
	Menu();
	~Menu();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	Obj* select;
};

