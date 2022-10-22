#pragma once
#include "Define.h"

class MyBitMap
{
public:
	MyBitMap();
	~MyBitMap();

public:
	HDC Get_memDC() { return memDC; }
	void Load_Bmp(const TCHAR* FilePath);
	void Release();

private:
	HDC memDC;
	HBITMAP bitmap;
	HBITMAP oldbmp;

};

