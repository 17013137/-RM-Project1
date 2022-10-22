#include "stdafx.h"
#include "Ending.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "Obj.h"
#include "ObjMgr.h"
#include "Player.h"
#include "TileMgr.h"


Ending::Ending()
{
}


Ending::~Ending()
{
	Release();
}

void Ending::Initialize()
{
	// MCI : �̵�� ��Ʈ�� �������̽�, ��Ƽ�̵�� ��ġ�� ����ϰ� ���ҽ� ������ ����ϱ� ���� �������̽�
	// �����, ���� �ֺ� ��ġ�� �����ϴ� ��ġ
	// MCIWndCreate : ��Ƽ�̵�� ����ϱ� ���� ������ â�� �����ϴ� �Լ�

	m_hVideo = MCIWndCreate(g_hwnd,  // �θ� ������ �ڵ�
		nullptr,	// MCI �����츦 ����ϴ� �ν��Ͻ� �ڵ�
		WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR,
		L"../Video/Ending.wmv"); // ��������� ���


								   //�������� ����� ũ�⸦ ����, �������� ���� ��� �������� ���� ũ���� ���
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_hVideo);
}

void Ending::Update()
{
}

int Ending::Late_Update()
{
	// ������ ��ü����		 <= ���� ����ǰ� �ִ� ������ ��ġ
	if (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo)
		|| KeyMgr::Get_Instance()->Key_DOWN(VK_RETURN))
	{
		SceneMgr::Get_Instance()->SceneChange(MENU);
		CTileMgr::Get_Instance()->Destroy_Instance();
		ObjMgr::Get_Instance()->Delete_ID(MONSTER);
		ObjMgr::Get_Instance()->Delete_ID(BULLET);
		ObjMgr::Get_Instance()->Delete_ID(PLAYER);
		return 0;
	}

	return 0;
}

void Ending::Render(HDC hdc)
{
}

void Ending::Release()
{
	MCIWndClose(m_hVideo);
}
