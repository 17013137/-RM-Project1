#pragma once
#include "BmpMgr.h"
#include "MyFunction.h"
#include "MyBitMap.h"

class BmpMgr
{
public:
	BmpMgr();
	~BmpMgr();

public:
	void Insert_Bmp(const TCHAR* FIlePath, const TCHAR* lmgKey);
	HDC Find_Image(const TCHAR* lmgkey);
	void Release();

public:
	static BmpMgr* Get_Instance(){
		if (m_instance == nullptr)
			m_instance = new BmpMgr;
		return m_instance;
	}
	static void Destory_Instance() {
		if (m_instance != nullptr) {
			delete m_instance;
			m_instance = nullptr;
		}
	}


private:
	static BmpMgr* m_instance;
	map<const TCHAR*, MyBitMap*> mapBit;

};

