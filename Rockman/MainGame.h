#pragma once
#include "Include.h"
#include "Player.h"
#include "ObjMgr.h"

class MainGame
{
public:
	MainGame();
	~MainGame();

public:
	void Initialize();
	void Update();
	int Late_Update();
	void Render();
	void Release();

private:
	HDC hdc;

	int				m_iFPS;
	TCHAR			m_szFPS[32];
	DWORD			m_dwTime;
};