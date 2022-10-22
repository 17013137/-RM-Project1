#pragma once
#include "Include.h"
#include "BmpMgr.h"
class Obj
{
public:
	Obj();
	virtual ~Obj();

public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual int Late_Update() PURE;
	virtual void Render(HDC hdc) PURE;
	virtual void Release() PURE;

public:
	void Update_Rect();
	const ID& Get_ID() { return id; }
	void Move_Frame();
	void Set_Pos(float _fX, float _fY);
	void Set_PosY(float Y) { info.fY = Y; }
	void Set_PosX(float X) { info.fX = X; }
	void Set_Dir(DIR _dir) { dir = _dir;}
	void Set_Dead() { dead = true; }
	void Set_isDamaged(bool flag) { isdamaged = flag; }
	void Set_Collison(bool flag) { collison = flag; }
	void Set_Super(bool flag) { collison = flag; }
	void Set_HP(int damage) { stat.hp -= damage; }
	void Set_FrameKey(TCHAR* _framekey) { frameKey = _framekey; }
	void Set_Target(Obj* _target) { target = _target; }

public:
	const int& Get_iDrawID() const { return m_iDrawID; }
	const INFO& Get_Info() const { return info; }
	const RECT& Get_RectInfo() const { return rectinfo; }
	const bool& Get_Jump() const { return jump; }
	const bool& Get_Collison() const { return collison; }
	const bool& Get_Super() const { return super; }
	const bool& Get_isDamaged() const { return isdamaged; }
	const STATE& Get_state() const { return state; }
	const STAT& Get_stat() const { return stat; }
	const DIR& Get_Dir() const { return dir; }

protected:
	float speed;

	FRAME frame;
	TCHAR* frameKey;

	BmpMgr* bmpmgr;
	RECT rectinfo;
	
	STAT stat;
	INFO info;
	STATE state;
	STATE preState;
	ID id;
	UI ui_id;
	DIR dir;
	bool jump;
	bool collison;
	int m_iDrawID;
	bool dead;
	bool isdamaged;
	bool super;
	Obj* target;
};

