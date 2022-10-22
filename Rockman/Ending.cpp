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
	// MCI : 미디어 컨트롤 인터페이스, 멀티미디어 장치를 재생하고 리소스 파일을 기록하기 위한 인터페이스
	// 오디오, 비디오 주변 장치를 제어하는 장치
	// MCIWndCreate : 멀티미디어 재생하기 위한 윈도우 창을 생성하는 함수

	m_hVideo = MCIWndCreate(g_hwnd,  // 부모 윈도우 핸들
		nullptr,	// MCI 윈도우를 사용하는 인스턴스 핸들
		WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR,
		L"../Video/Ending.wmv"); // 재생파일의 경로


								   //동영상을 재생할 크기를 설정, 설정하지 않을 경우 동영상의 원래 크기대로 출력
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_hVideo);
}

void Ending::Update()
{
}

int Ending::Late_Update()
{
	// 동영상 전체길이		 <= 현재 재생되고 있는 동영상 위치
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
