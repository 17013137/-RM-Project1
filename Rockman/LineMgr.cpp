#include "stdafx.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "MyLine.h"

LineMgr*	LineMgr::m_instance = nullptr;
LineMgr::LineMgr()
{
}

void 	LineMgr::Load_Line(void)
{
	HANDLE	hFile = CreateFile(L"../Data/Line.dat",	// 파일의 경로 및 이름 명시	
		GENERIC_READ,		// 파일 접근 모드, WRITE는 쓰기, READ는 읽기
		NULL,				// 공유방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가할 것인지 옵션, NULL 공유하지 않음
		NULL,				// 보안속성, NULL일 경우 기본값으로 설정
		OPEN_EXISTING,		// 파일이 없다면 생성, 있다면 덮어 쓰기, OPEN_EXITING 파일이 있을 경우에만 여는 옵션
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(읽기 전용, 숨김과 같은 속성을 의미), 아무런 속성이 없는 경우의 플래그
		NULL);	// 생성될 파일의 속성을 제공할 템플릿 파일이 있는 주소값

	if (INVALID_HANDLE_VALUE == hFile) // 개방 실패
	{
		MessageBox(g_hwnd, _T("LoadFail"), _T("Fail"), MB_OK);
		// 1인자 : 핸들, 어떤 프로세스에 메세지를 띄울 것인지 구분하기 위한 핸들
		// 2인자 : 메세지에 실제 출력하는 문자열
		// 3인자 : 팝업 창의 이름 문자열
		// 4인자 : OK 버튼
		return;
	}

	DWORD		dwByte = 0;
	LINEINFO	tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_linelist.push_back(new MyLine(tInfo));
	}

	// 파일 소멸
	CloseHandle(hFile);
	//MessageBox(g_hWnd, _T("Load 완료"), _T("Success"), MB_OK);
}


LineMgr::~LineMgr()
{
	Release();
}

void LineMgr::Initialize(void)
{
	Load_Line();
}

void LineMgr::Render(HDC hdc)
{
	for (auto& iter : m_linelist)
		iter->Redner(hdc);
}

void LineMgr::Release(void)
{
	for (auto& iter = m_linelist.begin(); iter != m_linelist.end(); iter++)
	{
		Safe_Delete(*iter);
		m_linelist.clear();
	}
}

bool LineMgr::Collision_Line(float * pX, float * pY)
{
	if (m_linelist.empty())
		return false;

	MyLine*	pTargetLine = nullptr;

	for (auto& iter : m_linelist)
	{
		if (*pX >= iter->Get_Info().tLeftPos.fX &&
			*pX <= iter->Get_Info().tRightPos.fX
			)
		{

			pTargetLine = iter;
		}
	}

	if (!pTargetLine)
		return false;

	// Y = (y2 - y1) / (x2 - x1) * (X - x1) + y1

	float	x1 = pTargetLine->Get_Info().tLeftPos.fX;
	float	y1 = pTargetLine->Get_Info().tLeftPos.fY;

	float	x2 = pTargetLine->Get_Info().tRightPos.fX;
	float	y2 = pTargetLine->Get_Info().tRightPos.fY;


	*pY = ((y2 - y1) / (x2 - x1)) * (*pX - x1) + y1 - 60;

	return true;
}
