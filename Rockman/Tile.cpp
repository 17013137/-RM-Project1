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
	BitBlt(hDC, // ������� dc, ���������� �׸��� �׸� dc
	int(m_tRect.left + iScrollX), // ���� ���� ��ġ x��ǥ
	int(m_tRect.top + iScrollY),                  // ���� ���� ��ġ y��ǥ
	(int)m_tInfo.fCX,             // ���� ���� �̹����� ���� ������
	(int)m_tInfo.fCY,             // ���� ���� �̹����� ���� ������
	hMemDC,						  // ���� ��Ʈ�� �̹����� ������ �ִ� dc
	TILECX * m_iDrawID,			  // ��Ʈ���� ����� ���� ��ǥ
	0,
	SRCCOPY);
	*/
	GdiTransparentBlt(hDC,			   // ������� dc, ���������� �׸��� �׸� dc
		int(rectinfo.left + iScrollX),  // ���� ���� ��ġ x��ǥ
		int(rectinfo.top + iScrollY),				   // ���� ���� ��ġ y��ǥ
		(int)info.fcX,			   // ���� ���� �̹����� ���� ������
		(int)info.fcY,			   // ���� ���� �̹����� ���� ������
		hMemDC,						   // ���� ��Ʈ�� �̹����� ������ �ִ� dc
		50 * m_iDrawID,							   // ��Ʈ���� ����� ���� ��ǥ
		0,
		50,							   // ������ ��Ʈ���� ����, ���� ������
		50,
		RGB(255, 0, 255));			// �����ϰ����ϴ� ����

}

void CTile::Release(void)
{

}
