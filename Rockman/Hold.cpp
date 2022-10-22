#include "stdafx.h"
#include "Hold.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "Button.h"
#include "Obj.h"
#include "ObjMgr.h"

Hold::Hold()
{
}


Hold::~Hold()
{
	Release();
}

void Hold::Initialize()
{
	bmpmgr->Insert_Bmp(L"../Image/05.Menu/Loading.bmp", L"LOADING");
}

void Hold::Update()
{
}

int Hold::Late_Update()
{
	return 0;
}

void Hold::Render(HDC hdc)
{
}

void Hold::Release()
{
}
