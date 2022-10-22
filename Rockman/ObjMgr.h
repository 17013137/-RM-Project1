#pragma once
#include "Include.h"
#include "Obj.h"
class ObjMgr
{
public:
	ObjMgr();
	~ObjMgr();
	
public:
	void Render(HDC hdc);
	void Update();
	int Late_Update();
	void Release();

public:

	void Set_PlayerInfo(float _x, float _y);
	void Set_Objlist(ID id, Obj* object);
	list<Obj*>* Get_objlist(ID id);
	Obj* Get_Player() {
		if (objlist[PLAYER].front() != nullptr)
			return objlist[PLAYER].front();
		return nullptr;
	}

public:
	void Delete_ID(ID eID);
	static ObjMgr* Get_Instance() {
		if (m_instance == nullptr)
			m_instance = new ObjMgr;
		return m_instance;
	}

	static void Destroy_Instance() {
		if (nullptr != m_instance)
			delete m_instance;
	}

private:
	static ObjMgr* m_instance;
	list<Obj*> objlist[ID_END];
};

