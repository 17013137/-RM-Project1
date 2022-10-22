#include "stdafx.h"
#include "MyLine.h"
#include "ScrollMgr.h"

MyLine::MyLine()
{
}

MyLine::MyLine(LINEINFO& _info)
	: m_tInfo(_info)
{
}

MyLine::MyLine(LINEPOS & tLeft, LINEPOS & tRight)
{
	m_tInfo.tLeftPos = tLeft;
	m_tInfo.tRightPos = tRight;
}


MyLine::~MyLine()
{
}

void MyLine::Redner(HDC hdc)
{
	float ScrollX = ScrollMgr::Get_Instance()->Get_ScrollX();

	MoveToEx(hdc, int(m_tInfo.tLeftPos.fX+ScrollX), (int)m_tInfo.tLeftPos.fY, nullptr);
	LineTo(hdc, int(m_tInfo.tRightPos.fX + ScrollX), (int)m_tInfo.tRightPos.fY);
}
