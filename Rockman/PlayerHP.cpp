#include "stdafx.h"
#include "PlayerHP.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"

PlayerHP::PlayerHP()
{
	ui_id = PLAYER_HP;
	Hp = 100;
	MaxHp = 100;
}


PlayerHP::~PlayerHP()
{
	Release();
}

void PlayerHP::Initialize()
{
	bmpmgr->Insert_Bmp(L"../Image/10.UI/PlayerHp/HPBar.bmp", L"PLAYERHP");
	bmpmgr->Insert_Bmp(L"../Image/10.UI/PlayerHp/CurrentHP.bmp", L"CURRENT_HP");
	bmpmgr->Insert_Bmp(L"../Image/10.UI/PlayerHp/DecreaseHP.bmp", L"DECREASE_HP");
	MaxHp = ObjMgr::Get_Instance()->Get_Player()->Get_stat().maxhp;
	info.fX = 50.f;
	info.fY = 200.f;

	info.fcX = 100.f;
	info.fcY = 146.f;

	frame.Scean = 0;
	frame.Start = 0;
	frame.End = 0;
	frame.frspeed = 0;

	Update_Rect();
	frameKey = L"PLAYERHP";
}

int PlayerHP::Update()
{
	if(ObjMgr::Get_Instance()->Get_Player() != nullptr)
		Hp = ObjMgr::Get_Instance()->Get_Player()->Get_stat().hp;
	return 0;
}

int PlayerHP::Late_Update()
{
	return 0;
}

void PlayerHP::Render(HDC hdc)
{
	//Rectangle(hdc, rectinfo.left, rectinfo.top, rectinfo.right, rectinfo.bottom);
	HDC memDC = bmpmgr->Find_Image(frameKey); //HPBar
	GdiTransparentBlt(hdc,
		int(rectinfo.left),
		int(rectinfo.top),
		100,
		146,
		memDC,
		frame.Start * 100,
		frame.Scean * 146,
		100,
		146,
		RGB(200, 0, 255));

	HDC memDC2 = BmpMgr::Get_Instance()->Find_Image(L"CURRENT_HP"); //Current HP
	BitBlt(hdc, info.fX-23, rectinfo.top+5, 14, 90, memDC2, 0, (Hp/MaxHp)*90-90, SRCCOPY);

	//HDC memDC3 = BmpMgr::Get_Instance()->Find_Image(L"DECREASE_HP"); //Decrease HP
	//BitBlt(hdc, info.fX - 23, rectinfo.top + 5, 14, 90, memDC3, 0, 0, SRCCOPY);

}

void PlayerHP::Release()
{
}
