#include "stdafx.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

ObjMgr* ObjMgr::m_instance = nullptr;
ObjMgr::ObjMgr()
{
}


ObjMgr::~ObjMgr()
{
	Release();
}

void ObjMgr::Render(HDC hdc)
{


	for (int i = 0; i < ID_END; i++) {
		for (auto& iter = objlist[i].begin(); iter != objlist[i].end() ; iter++)
		{
			(*iter)->Render(hdc);
		}
	}
}

void ObjMgr::Update()
{
	int Event = 0;
	for (int i = 0; i < ID_END; i++) {
		auto& iter = objlist[i].begin();
		for (; iter != objlist[i].end(); )
		{
			Event = (*iter)->Update();
			if (OBJ_DEAD == Event) {
				Safe_Delete<Obj*>(*iter);
				iter = objlist[i].erase(iter);
			}
			else
				iter++;
		}
	}

}

int ObjMgr::Late_Update()
{
	for (int i = 0; i < ID_END; i++) {
		for (auto& iter = objlist[i].begin(); iter != objlist[i].end(); iter++)
		{
			(*iter)->Late_Update();
		}
	}
	return 0;
}

void ObjMgr::Set_PlayerInfo(float _x, float _y)
{
	if (objlist[PLAYER].front() != nullptr) {
		objlist[PLAYER].front()->Set_PosX(_x);
		objlist[PLAYER].front()->Set_PosY(_y);
	}
	else
		MessageBox(g_hwnd, L"ERROR!", L"!", MB_OK);
}

void ObjMgr::Set_Objlist(ID id, Obj* object)
{
	if (object == nullptr || id >= ID_END || nullptr == object) {
		return;
	}

	objlist[id].push_back(object);
}

list<Obj*>* ObjMgr::Get_objlist(ID id)
{
	if (id >= ID_END) {
		return nullptr;
	}

	return &objlist[id];
}

void ObjMgr::Delete_ID(ID eID)
{
	for (auto& iter : objlist[eID]) {
		Safe_Delete(iter);
	}
	objlist[eID].clear();
}

void ObjMgr::Release()
{
	for (int i = 0; i < ID_END; i++) {
		for_each(objlist[i].begin(), objlist[i].end(), Safe_Delete<Obj*>);
		objlist[i].clear();
	}
}