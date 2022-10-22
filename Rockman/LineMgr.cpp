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
	HANDLE	hFile = CreateFile(L"../Data/Line.dat",	// ������ ��� �� �̸� ���	
		GENERIC_READ,		// ���� ���� ���, WRITE�� ����, READ�� �б�
		NULL,				// �������, ������ �����ִ� ���¿��� �ٸ� ���μ����� ���� �� �� �㰡�� ������ �ɼ�, NULL �������� ����
		NULL,				// ���ȼӼ�, NULL�� ��� �⺻������ ����
		OPEN_EXISTING,		// ������ ���ٸ� ����, �ִٸ� ���� ����, OPEN_EXITING ������ ���� ��쿡�� ���� �ɼ�
		FILE_ATTRIBUTE_NORMAL, // ���� �Ӽ�(�б� ����, ����� ���� �Ӽ��� �ǹ�), �ƹ��� �Ӽ��� ���� ����� �÷���
		NULL);	// ������ ������ �Ӽ��� ������ ���ø� ������ �ִ� �ּҰ�

	if (INVALID_HANDLE_VALUE == hFile) // ���� ����
	{
		MessageBox(g_hwnd, _T("LoadFail"), _T("Fail"), MB_OK);
		// 1���� : �ڵ�, � ���μ����� �޼����� ��� ������ �����ϱ� ���� �ڵ�
		// 2���� : �޼����� ���� ����ϴ� ���ڿ�
		// 3���� : �˾� â�� �̸� ���ڿ�
		// 4���� : OK ��ư
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

	// ���� �Ҹ�
	CloseHandle(hFile);
	//MessageBox(g_hWnd, _T("Load �Ϸ�"), _T("Success"), MB_OK);
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
