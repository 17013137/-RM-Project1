#pragma once

class Obj;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

private:
	static bool			Check_Sphere(Obj* pDest, Obj* pSrc);
	static bool			Check_Rect(Obj* pDest, Obj* pSrc, float* _pX, float* _pY);

public:
	//static void		Collision_Rect(list<Obj*>& Dest, list<Obj*>& Src);
	static void		Collision_Sphere(list<Obj*>& Dest, list<Obj*>& Src);
	static void		Collision_RectEx(list<Obj*>* Dest, list<Obj*>* Src);
	static void		Collision_Obj(Obj* player, list<Obj*>* Src);
	static int		Collision_TILE(Obj* player);
};

