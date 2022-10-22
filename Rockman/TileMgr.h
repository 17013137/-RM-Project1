#pragma once
#include "Tile.h"
#include "Enum.h"
class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void Initialize(void);
	void Update(void);
	int Late_Update(void);
	void Render(HDC hDC);
	void Release(void);
	void Picking_Tile(POINT& pt, const int& iDrawID, const int& iOption);
	//void	Save_Data(void);
	void	Load_Data(SCENEID _id);
	vector<Obj*> Get_Tileinfo() { return m_vecTile; }

public:
	static CTileMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CTileMgr;

		return m_pInstance;
	}
	static void			Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static		CTileMgr*	m_pInstance;
	vector<Obj*>			m_vecTile;
};

