#pragma once
#include "Scene.h"
#include "Player.h"
#include "ObjMgr.h"
#include "UIMgr.h"

class BossStage : public Scene
{
public:
	BossStage();
	~BossStage();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual int Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

public:
	void offset();

private:
	ObjMgr* objmgr;
	UIMgr* uimgr;
	Player player;
};

