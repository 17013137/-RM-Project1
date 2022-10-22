#pragma once
#include "Define.h"

class KeyMgr
{
public:
	KeyMgr();
	~KeyMgr();

public:
	bool Key_Pressing(int Key);
	bool Key_UP(int Key);
	bool Key_DOWN(int Key);
	void Check_isdown() { isdown == true ? false : true; }
	bool Get_isdown() { return isdown; }
public:
	static void Destroy_Instance() {
		if (keymgr != nullptr) {
			delete keymgr;
			keymgr = nullptr;
		}
	}
	static KeyMgr* Get_Instance() {
		if (keymgr == nullptr)
			keymgr = new KeyMgr;

		return keymgr;
	}
	bool isdown;
private:
	static KeyMgr* keymgr;
	bool keyState[VK_MAX];
};

