#pragma once
#include "Include.h"
#include "BmpMgr.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual int Late_Update() PURE;
	virtual void Render(HDC hdc) PURE;
	virtual void Release() PURE;

protected:
	BmpMgr* bmpmgr;
};

