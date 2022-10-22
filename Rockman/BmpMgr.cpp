#include "stdafx.h"
#include "BmpMgr.h"
#include "MyFunction.h"
#include "MyBitMap.h"


BmpMgr* BmpMgr::m_instance = nullptr;
BmpMgr::BmpMgr()
{
}


BmpMgr::~BmpMgr()
{
	Release();
}

void BmpMgr::Insert_Bmp(const TCHAR * FilePath, const TCHAR* ImgKey)
{
	auto iter = find_if(mapBit.begin(), mapBit.end(), Find_Tag(ImgKey));

	if (iter == mapBit.end()) {
		MyBitMap* Bmp = new MyBitMap;
		Bmp->Load_Bmp(FilePath);

		mapBit.emplace(ImgKey, Bmp);
	}
}

HDC BmpMgr::Find_Image(const TCHAR * ImgKey)
{
	auto iter = find_if(mapBit.begin(), mapBit.end(), Find_Tag(ImgKey));

	if (iter == mapBit.end()) {
		return nullptr;
	}

	return iter->second->Get_memDC();

}

void BmpMgr::Release()
{
	for_each(mapBit.begin(), mapBit.end(), CDeleteMap());
	mapBit.clear();
}
