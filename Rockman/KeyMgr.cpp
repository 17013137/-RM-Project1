#include "stdafx.h"
#include "KeyMgr.h"

KeyMgr* KeyMgr::keymgr = nullptr;
KeyMgr::KeyMgr()
{
	isdown = false;
	ZeroMemory(keyState, sizeof(keyState));
}


KeyMgr::~KeyMgr()
{
}

bool KeyMgr::Key_Pressing(int Key)
{
	if (GetAsyncKeyState(Key) & 0x8000)
		return true;

	return false;
}
bool KeyMgr::Key_DOWN(int Key)
{
	if (!keyState[Key] && (GetAsyncKeyState(Key) & 0x8000)) {
		keyState[Key] = !keyState[Key];
		return true;
	}

	if (keyState[Key] && !(GetAsyncKeyState(Key) & 0x8000)) {
		keyState[Key] = !keyState[Key];
	}

	return false;
}

bool KeyMgr::Key_UP(int Key)
{
	if (keyState[Key] && !(GetAsyncKeyState(Key) & 0x8000)) {
		keyState[Key] = !keyState[Key];
		
		return true;
	}

	if (!keyState[Key] && (GetAsyncKeyState(Key) & 0x8000)) {
		keyState[Key] = !keyState[Key];

	}

	return false;
}

