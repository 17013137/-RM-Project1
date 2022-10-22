#pragma once


class ScrollMgr
{
public:
	ScrollMgr();
	~ScrollMgr();

public:
	static ScrollMgr* Get_Instance() {
		if (m_instance == nullptr)
			m_instance = new ScrollMgr;

		return m_instance;
	}
	void Destory_Instance() {
		if (m_instance != nullptr)
			delete m_instance;
	}

public:
	void Set_StageSizeX(float _X) { X = _X; }
	void Set_StageSizeY(float _Y) { Y = _Y; }
	float Get_StageSizeX() { return X; }
	float Get_StageSizeY() { return Y; }

	void Set_ScrollX(float _fX) { scrollX += _fX; }
	void Set_ScrollY(float _fY) { scrollY += _fY; }
	float Get_ScrollX() { return scrollX; }
	float Get_ScrollY() { return scrollY; }
	void Scroll_Lock();

private:
	static ScrollMgr* m_instance;
	float scrollX;
	float scrollY;

	float X;
	float Y;
};

