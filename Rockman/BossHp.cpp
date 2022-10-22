#include "stdafx.h"
#include "BossHp.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"

BossHp::BossHp()
{
	ui_id = BOSS_HP;
	Hp = 100;
	MaxHp = 100;
}


BossHp::~BossHp()
{
	Release();
}

void BossHp::Initialize()
{
	bmpmgr->Insert_Bmp(L"../Image/10.UI/BossHp/Boss_HPBar.bmp", L"BOSS_HP_BAR");
	bmpmgr->Insert_Bmp(L"../Image/10.UI/BossHp/Boss_HP.bmp", L"BOSS_HP");
	MaxHp = target->Get_stat().maxhp;
	info.fX = 750.f;
	info.fY = 200.f;

	info.fcX = 80.f;
	info.fcY = 199.f;

	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 0;
	frame.frspeed = 0;

	Update_Rect();
	frameKey = L"BOSS_HP_BAR";
}

int BossHp::Update()
{
	Hp = target->Get_stat().hp;
	return 0;
}

int BossHp::Late_Update()
{
	return 0;
}

void BossHp::Render(HDC hdc)
{
	HDC memDC = bmpmgr->Find_Image(frameKey); //HPBar
	GdiTransparentBlt(hdc,
		int(rectinfo.left),
		int(rectinfo.top),
		80,
		199,
		memDC,
		frame.Start * 80,
		frame.Scean * 199,
		80,
		199,
		RGB(200, 0, 255));

	HDC memDC2 = BmpMgr::Get_Instance()->Find_Image(L"BOSS_HP"); //Current HP
	BitBlt(hdc, info.fX-7, rectinfo.top + 5, 14, 133, memDC2, 0, (Hp / MaxHp) * 133 - 133, SRCCOPY);
	TCHAR		szBuff[32] = L"";

	swprintf_s(szBuff, L"asd : %f", (Hp / MaxHp) * 133 - 133);
	SetWindowText(g_hwnd, szBuff);


}

void BossHp::Release()
{
}
