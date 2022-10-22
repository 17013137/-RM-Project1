#include "stdafx.h"
#include "TileMgr.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Enum.h"

CTileMgr*	CTileMgr::m_pInstance = NULL;

CTileMgr::CTileMgr()
{
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize(void)
{
	BmpMgr::Get_Instance()->Insert_Bmp(L"../Image/06.Tile/Tile.bmp", L"Tile");

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = float((TILECX * j) + (TILECX >> 1));
			float fY = float((TILECY * i) + (TILECY >> 1));

			m_vecTile.push_back(CAbstractFactory<CTile>::Create(fX, fY));
		}
	}

}

void CTileMgr::Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Update();
}

int CTileMgr::Late_Update(void)
{
	for (auto& iter : m_vecTile)
		iter->Late_Update();
	return 0;
}

void CTileMgr::Render(HDC hDC)
{
	/*
	for (auto& iter : m_vecTile)
	iter->Render(hDC);
	*/

	int	iCullX = abs((int)ScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	int	iCullY = abs((int)ScrollMgr::Get_Instance()->Get_ScrollY() / TILECY);

	//				3 + 12.
	int	iCullEndX = iCullX + (WINCX / (TILECX)); // (+2�� �ϴ� ������ Ÿ�� ������ Ư���� �� 800, 600���� �������� �ʱ� ������ �� ��ĭ �� �����ְ� ����ؼ� �ڿ������� ���̱� ����)
	int	iCullEndY = iCullY + (WINCY / (TILECY));



	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int		iIndex = i * TILEX + j;

			if (0 > iIndex || m_vecTile.size() < (size_t)iIndex)
				continue;

			m_vecTile[iIndex]->Render(hDC);
		}
	}

}

void CTileMgr::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<Obj*>);
	m_vecTile.clear();
}

void CTileMgr::Picking_Tile(POINT& pt, const int& iDrawID, const int& iOption)
{
	int		iX = pt.x / TILECX;
	int		iY = pt.y / TILECY;

	int		iIndex = iY * TILEX + iX;

	if (0 > iIndex || m_vecTile.size() <= (size_t)iIndex)
		return;


	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(iOption);
}

void CTileMgr::Load_Data(SCENEID _id)
{
	HANDLE	hFile = nullptr;
	switch (_id)
	{
	case STAGE:
		hFile = CreateFile(L"../Data/Stage1/Tile.dat",	// ������ ��� �� �̸� ���	
			GENERIC_READ,		// ���� ���� ���, WRITE�� ����, READ�� �б�
			NULL,				// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�� ������ �ɼ�, NULL �������� ����
			NULL,				// ���ȼӼ�, NULL�� ��� �⺻������ ����
			OPEN_EXISTING,		// ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXITING ������ ���� ��쿡�� ���� �ɼ�
			FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ����� ���� �Ӽ��� �ǹ�), �ƹ��� �Ӽ��� ���� ����� �÷���
			NULL);	// ������ ������ �Ӽ��� ������ ���ø� ������ �ִ� �ּҰ�
		break;
	case STAGE_BOSS:
		hFile = CreateFile(L"../Data/Stage1_boss/Tile.dat",	// ������ ��� �� �̸� ���	
			GENERIC_READ,		// ���� ���� ���, WRITE�� ����, READ�� �б�
			NULL,				// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�� ������ �ɼ�, NULL �������� ����
			NULL,				// ���ȼӼ�, NULL�� ��� �⺻������ ����
			OPEN_EXISTING,		// ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXITING ������ ���� ��쿡�� ���� �ɼ�
			FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ����� ���� �Ӽ��� �ǹ�), �ƹ��� �Ӽ��� ���� ����� �÷���
			NULL);	// ������ ������ �Ӽ��� ������ ���ø� ������ �ִ� �ּҰ�
		break;
	}
	

	DWORD		dwByte = 0;
	INFO	tInfo{};
	int		iDrawID = 0, iOption = 0;

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		Obj*	 pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pObj)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pObj)->Set_Option(iOption);

		m_vecTile.push_back(pObj);
	}

	// ���� �Ҹ�
	CloseHandle(hFile);
}
