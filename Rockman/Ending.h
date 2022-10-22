#pragma once
#include "Scene.h"

class Ending : public Scene
{
public:
	Ending();
	virtual ~Ending();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

private:
	HWND		m_hVideo;

};

