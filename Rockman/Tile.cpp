#include "stdafx.h"
#include "Tile.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"


CTile::CTile()
{
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize(void)
{
	m_iDrawID = 0;
	m_iOption = 0;

	info.fcX = TILECX;
	info.fcY = TILECY;

}

int CTile::Update(void)
{
	Update_Rect();

	return OBJ_NOEVENT;
}

int CTile::Late_Update(void)
{
	return 0;
}

void CTile::Render(HDC hDC)
{
	int	iScrollX = (int)ScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)ScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = BmpMgr::Get_Instance()->Find_Image(L"Tile");

	/*
	BitBlt(hDC, // 복사받을 dc, 최종적으로 그림을 그릴 dc
	int(m_tRect.left + iScrollX), // 복사 받을 위치 x좌표
	int(m_tRect.top + iScrollY),                  // 복사 받을 위치 y좌표
	(int)m_tInfo.fCX,             // 복사 받을 이미지의 가로 사이즈
	(int)m_tInfo.fCY,             // 복사 받을 이미지의 세로 사이즈
	hMemDC,						  // 현재 비트맵 이미지를 가지고 있는 dc
	TILECX * m_iDrawID,			  // 비트맵을 출력할 시작 좌표
	0,
	SRCCOPY);
	*/
	GdiTransparentBlt(hDC,			   // 복사받을 dc, 최종적으로 그림을 그릴 dc
		int(rectinfo.left + iScrollX),  // 복사 받을 위치 x좌표
		int(rectinfo.top + iScrollY),				   // 복사 받을 위치 y좌표
		(int)info.fcX,			   // 복사 받을 이미지의 가로 사이즈
		(int)info.fcY,			   // 복사 받을 이미지의 세로 사이즈
		hMemDC,						   // 현재 비트맵 이미지를 가지고 있는 dc
		50 * m_iDrawID,							   // 비트맵을 출력할 시작 좌표
		0,
		50,							   // 복사할 비트맵의 가로, 세로 사이즈
		50,
		RGB(255, 0, 255));			// 제거하고자하는 색상

}

void CTile::Release(void)
{

}
