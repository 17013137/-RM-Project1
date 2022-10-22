#include "stdafx.h"
#include "ScrollMgr.h"
#include "Include.h"

ScrollMgr* ScrollMgr::m_instance = nullptr;
ScrollMgr::ScrollMgr()
	:scrollX(0.f), scrollY(0.f), X(0.f), Y(0.f)
{
}


ScrollMgr::~ScrollMgr()
{
}

void ScrollMgr::Scroll_Lock()
{
	
	if (0.f < scrollX) {
		scrollX = 0.f;
	}
	if (0.f < scrollY)
		scrollY = 0.f;

	if (scrollX < WINCX - X) {

		scrollX = WINCX - X;
	}

	if (scrollY > WINCY - Y) {
		scrollY = WINCY - Y;
	}
}
