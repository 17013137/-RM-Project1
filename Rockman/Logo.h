#pragma once
#include "Scene.h"

class Logo : public Scene
{
public:
	Logo();
	~Logo();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

};

