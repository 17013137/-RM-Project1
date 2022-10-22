#include "stdafx.h"
#include "MyBitMap.h"


MyBitMap::MyBitMap()
{
	
}


MyBitMap::~MyBitMap()
{
	Release();
}

void MyBitMap::Load_Bmp(const TCHAR * FilePath)
{
	HDC hdc = GetDC(g_hwnd);
	memDC = CreateCompatibleDC(hdc);
	ReleaseDC(g_hwnd, hdc);

	bitmap = (HBITMAP)LoadImage(NULL,
		FilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	oldbmp = (HBITMAP)SelectObject(memDC, bitmap);
}

void MyBitMap::Release()
{
	SelectObject(memDC, oldbmp);

	DeleteObject(bitmap);
	DeleteDC(memDC);
}
