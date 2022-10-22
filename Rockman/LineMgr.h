#pragma once

#include "MyLine.h"
#include "Obj.h"

class LineMgr
{
	enum LINEDIR { LINE_LEFT, LINE_RIGHT, LINE_END };
public:
	LineMgr();
	~LineMgr();

public:
	void		Initialize(void);
	void		Render(HDC _HDC);
	void		Release(void);
	void		Load_Line();
	bool		Collision_Line(float* pX, float* pY);

public:
	static LineMgr*		Get_Instance(void)
	{
		if (nullptr == m_instance)
			m_instance = new LineMgr;

		return m_instance;
	}
	static void			Destroy_Instance(void)
	{
		if (nullptr != m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

private:
	static LineMgr* m_instance;
	list<MyLine*> m_linelist;
	LINEPOS					m_tLinePos[LINE_END];
};

