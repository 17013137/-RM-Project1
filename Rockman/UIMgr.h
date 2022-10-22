#pragma once
#include "Include.h"
#include "Obj.h"

class UIMgr
{
public:
	UIMgr();
	~UIMgr();

public:
	void Render(HDC hdc);
	void Release();
	void Update();
	int Late_Update();

public:
	void Add_Objlist(UI id, Obj* object);
	list<Obj*>* Get_uilist(UI id);
	void Delete_UI(UI eID);

	static UIMgr* Get_Instance() {
		if (ui_instance == nullptr)
			ui_instance = new UIMgr;
		return ui_instance;
	}

	static void Destroy_Instance() {
		if (nullptr != ui_instance)
			delete ui_instance;
	}

private:
	static UIMgr* ui_instance;
	list<Obj*> uilist[UI_END];
};

