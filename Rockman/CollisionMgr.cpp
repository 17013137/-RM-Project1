#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "TileMgr.h"
#include "Include.h"
#include "ObjMgr.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}


/*
void CCollisionMgr::Collision_Rect(list<Obj*>& Dest, list<Obj*>& Src)
{
	RECT	rc{};

	for (auto& DestIter : Dest)
	{
		for (auto& SrcIter : Src)
		{
			if (IntersectRect(&rc, &(DestIter->Get_Rect()), &(SrcIter->Get_Rect())))
			{
				DestIter->Set_Dead();
				SrcIter->Set_Dead();
			}
		}
	}
}
*/

bool CCollisionMgr::Check_Sphere(Obj* pDest, Obj* pSrc)
{
	float		fWidth = fabs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = fabs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	float		fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDest->Get_Info().fcX + pSrc->Get_Info().fcX) * 0.5f;

	return fRadius > fDistance;		// 충돌 했다
}


bool CCollisionMgr::Check_Rect(Obj* pDest, Obj* pSrc, float* _pX, float* _pY)
{
	float		fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	// float		fCX = pDest->Get_Info().fCX / 2.f + pSrc->Get_Info().fCX / 2.f;
	// 위의 식을 아래 식으로 변경했을 뿐
	float		fCX = (pDest->Get_Info().fcX + pSrc->Get_Info().fcX) * 0.5f;
	float		fCY = (pDest->Get_Info().fcY + pSrc->Get_Info().fcY) * 0.5f;

	if (fCX > fWidth && fCY > fHeight)
	{

		*_pX = fCX - fWidth;
		*_pY = fCY - fHeight;

		return true;
	}
	return false;
}

void CCollisionMgr::Collision_RectEx(list<Obj*>* Dest, list<Obj*>* Src)
{
	RECT	rc{};

	float		fWidth, fHeight;



	for (auto& DestIter : *Dest)
	{
		for (auto& SrcIter : *Src)
		{

			if (Check_Rect(DestIter, SrcIter, &fWidth, &fHeight))
			{

				// 상하 충돌
				if (fWidth > fHeight)
				{
					// 하 충돌
					if (DestIter->Get_Info().fY < SrcIter->Get_Info().fY)
						SrcIter->Set_PosY(fHeight);
					// 상 충돌
					else
						SrcIter->Set_PosY(-fHeight-10);
				}
				// 좌우 충돌
				else
				{
					// 우 충돌
					if (DestIter->Get_Info().fX < SrcIter->Get_Info().fX)
						SrcIter->Set_PosX(fWidth);
					// 좌 충돌
					else
						SrcIter->Set_PosX(-fWidth);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Obj(Obj * player, list<Obj*>* Src)
{
	float		fWidth, fHeight;
	for (auto& iter : *Src) {
		if (iter->Get_ID() == OBSTACLE && player->Get_ID() == PLAYER) { //플레이어 + 장애물 충돌
			if (Check_Rect(iter, player, &fWidth, &fHeight)) {
				player->Set_PosX(iter->Get_RectInfo().left - player->Get_Info().fcX / 2);
			}
		}
		else if (player->Get_ID() == OBSTACLE && iter->Get_ID() == BULLET) { //총알 + 장애물 충돌
			if (Check_Rect(iter, player, &fWidth, &fHeight)) {
				player->Set_HP(iter->Get_stat().damage);  //데미지입음
				iter->Set_Dead();
				if (player->Get_stat().hp <= 0)  // 피가 0이하일시
					player->Set_Dead();
			}
		}
		else {
			if (Check_Sphere(iter, player) && !player->Get_isDamaged() && !player->Get_Super()) {
				if (player->Get_ID() == PLAYER && iter->Get_ID() != OBSTACLE) //피격
					player->Set_isDamaged(true);
				player->Set_HP(iter->Get_stat().damage);  //데미지입음
				if (player->Get_stat().hp <= 0)  // 피가 0이하일시
					player->Set_Dead();
			}
		}
	}


}

int CCollisionMgr::Collision_TILE(Obj* player)
{
	float		fWidth, fHeight;
	vector<Obj*> tile_list = CTileMgr::Get_Instance()->Get_Tileinfo();

	for (auto iter : tile_list) {
		if (iter->Get_iDrawID() == 1 && Check_Rect(iter, player, &fWidth, &fHeight)) {
			if ((iter->Get_RectInfo().right >= player->Get_RectInfo().right) && iter->Get_RectInfo().top < player->Get_RectInfo().bottom - 10) {
				if (player->Get_Jump() == true)
					player->Set_Collison(true);
				player->Set_PosX(iter->Get_RectInfo().left - player->Get_Info().fcX / 2);
				return 2;
			}
			else if((iter->Get_RectInfo().right <= player->Get_RectInfo().right) && iter->Get_RectInfo().top < player->Get_RectInfo().bottom - 10) {
				player->Set_PosX(iter->Get_RectInfo().right + player->Get_Info().fcX / 2);
				return 2;
			}
			else {
				if (player->Get_state() != JUMPUP || player->Get_state() != JUMP_ATTACKUP) {
					player->Set_PosY(iter->Get_RectInfo().top - player->Get_Info().fcY / 2 + 1);
					player->Set_Collison(false);
					return 1;
				}
			}
				//MessageBox(g_hwnd, L"a", L"a", MB_OK);
				// 상하 충돌
				/*
				if (fWidth > fHeight)
				{

					// 하 충돌
					if (iter->Get_Info().fY < iter->Get_Info().fY) {
						player->Set_PosY(fHeight);
						//SrcIter->Set_PosY(fHeight);
						return 2;
					}
					// 상 충돌
					else {
						player->Set_PosY(iter->Get_RectInfo().top);
						//SrcIter->Set_PosY(-fHeight);
						return 1;
					}
				}
				// 좌우 충돌
				else
				{
					// 우 충돌
					if (iter->Get_Info().fX < iter->Get_Info().fX) {
						player->Set_PosX(fWidth);
						//	SrcIter->Set_PosX(fWidth);
						return 4;
					}
					// 좌 충돌
					else {
						player->Set_PosX(-fWidth);
						//	SrcIter->Set_PosX(-fWidth);
						return 3;
					}
				}
			}
			*/
			}
	}
	return 0;
}


void CCollisionMgr::Collision_Sphere(list<Obj*>& Dest, list<Obj*>& Src)
{
	for (auto& DestIter : Dest)
	{
		for (auto& SrcIter : Src)
		{
			if (Check_Sphere(DestIter, SrcIter))
			{
				DestIter->Set_Dead();
				SrcIter->Set_Dead();
			}
		}
	}

}

