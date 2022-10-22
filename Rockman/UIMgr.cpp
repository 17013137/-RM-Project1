#include "stdafx.h"
#include "UIMgr.h"

UIMgr* UIMgr::ui_instance = nullptr;
UIMgr::UIMgr()
{
}


UIMgr::~UIMgr()
{
	Release();
}

void UIMgr::Render(HDC hdc)
{
	for (int i = 0; i < UI_END; i++) {
		for (auto& iter = uilist[i].begin(); iter != uilist[i].end(); iter++)
		{
			(*iter)->Render(hdc);
		}
	}
}

void UIMgr::Update()
{
	int Event = 0;

	for (int i = 0; i < UI_END; i++) {
		auto& iter = uilist[i].begin();
		for (; iter != uilist[i].end(); )
		{
			Event = (*iter)->Update();
			if (OBJ_DEAD == Event) {
				Safe_Delete<Obj*>(*iter);
				iter = uilist[i].erase(iter);
			}
			else
				iter++;
		}
	}

}

int UIMgr::Late_Update()
{
	for (int i = 0; i < UI_END; i++) {
		for (auto& iter = uilist[i].begin(); iter != uilist[i].end(); iter++)
		{
			(*iter)->Late_Update();
		}
	}
	return 0;
}



void UIMgr::Add_Objlist(UI id, Obj * object)
{
	if (object == nullptr || id >= UI_END || nullptr == object) {
		return;
	}

	uilist[id].push_back(object);
}

list<Obj*>* UIMgr::Get_uilist(UI id)
{
	if (id >= UI_END) {
		return nullptr;
	}

	return &uilist[id];
}

void UIMgr::Delete_UI(UI eID)
{
	for (auto& iter : uilist[eID]) {
		Safe_Delete(iter);
	}
	uilist[eID].clear();
}

void UIMgr::Release()
{
	for (int i = 0; i < UI_END; i++) {
		for_each(uilist[i].begin(), uilist[i].end(), Safe_Delete<Obj*>);
		uilist[i].clear();
	}
}

