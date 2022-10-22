#pragma once
#include "Include.h"

class MyLine
{
public:
	MyLine();
	MyLine(LINEINFO& _info);
	MyLine(LINEPOS& tLeft, LINEPOS& tRight);
	~MyLine();

public:
	const	LINEINFO& Get_Info(void) const { return m_tInfo; }

public:
	void Redner(HDC hdc);

private:
	LINEINFO m_tInfo;

};

