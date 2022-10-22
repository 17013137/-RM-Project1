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
	int	iCullEndX = iCullX + (WINCX / (TILECX)); // (+2를 하는 이유는 타일 사이즈 특성상 딱 800, 600으로 떨어지지 않기 때문에 한 두칸 더 여유있게 출력해서 자연스럽게 보이기 위함)
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
		hFile = CreateFile(L"../Data/Stage1/Tile.dat",	// 파일의 경로 및 이름 명시	
			GENERIC_READ,		// 파일 접근 모드, WRITE는 쓰기, READ는 읽기
			NULL,				// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인지 옵션, NULL 공유하지 않음
			NULL,				// 보안속성, NULL일 경우 기본값으로 설정
			OPEN_EXISTING,		// 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXITING 파일이 있을 경우에만 여는 옵션
			FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김과 같은 속성을 의미), 아무런 속성이 없는 경우의 플래그
			NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일이 있는 주소값
		break;
	case STAGE_BOSS:
		hFile = CreateFile(L"../Data/Stage1_boss/Tile.dat",	// 파일의 경로 및 이름 명시	
			GENERIC_READ,		// 파일 접근 모드, WRITE는 쓰기, READ는 읽기
			NULL,				// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인지 옵션, NULL 공유하지 않음
			NULL,				// 보안속성, NULL일 경우 기본값으로 설정
			OPEN_EXISTING,		// 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXITING 파일이 있을 경우에만 여는 옵션
			FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김과 같은 속성을 의미), 아무런 속성이 없는 경우의 플래그
			NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일이 있는 주소값
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

	// 파일 소멸
	CloseHandle(hFile);
}
