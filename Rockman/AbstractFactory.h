#pragma once
#include "Obj.h"

// 추상 팩토리 패턴

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	static	Obj*		Create()
	{
		Obj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}
	
	static	Obj*		Create(float _fX, float _fY)
	{
		Obj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);

		return pObj;
	}

	static	Obj*		Create(float _fX, float _fY, DIR eDir)
	{
		Obj*		pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Dir(eDir);
		pObj->Initialize();

		return pObj;
	}

	static	Obj*		Create(float _fX, float _fY, Obj* obj)
	{
		Obj*		pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Target(obj);
		pObj->Initialize();

		return pObj;
	}
};