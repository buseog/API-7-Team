#include "StdAfx.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "Item.h"
#include "Box.h"

CCollisionMgr::CCollisionMgr(void)
{
}

CCollisionMgr::~CCollisionMgr(void)
{
}

void CCollisionMgr::CollisionRange(list<CObj*>* pTemp, list<CObj*>* pTemp2)		// pTemp = 불렛
{
	for(list<CObj*>::iterator iter = pTemp->begin();
		iter != pTemp->end();)
	{
		if ((*iter)->GetInfo().fX + CObj::GetScrollX() >= 800 || (*iter)->GetInfo().fX + CObj::GetScrollX() <= 0 || (*iter)->GetInfo().fY >= 600 || (*iter)->GetInfo().fY <= 0)
		{
			Safe_Delete(*iter);
			iter = pTemp->erase(iter);
		}
		else
		{
			++iter;
		}
	}

	for(list<CObj*>::iterator iter = pTemp2->begin();
		iter != pTemp2->end();)
	{
		if ((*iter)->GetInfo().fX + CObj::GetScrollX() >= 800 || (*iter)->GetInfo().fX + CObj::GetScrollX() <= 0 || (*iter)->GetInfo().fY >= 600 || (*iter)->GetInfo().fY <= 0)
		{
			Safe_Delete(*iter);
			iter = pTemp2->erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CCollisionMgr::CollisionBox(list<CObj*>* pTemp, list<CObj*>* pTemp2)		// pTemp = 플레이어 , pTemp2 = 박스를 지정.
{
	RECT rcCol;

	for (list<CObj*>::iterator iter = pTemp->begin(); iter != pTemp->end(); ++iter)
	{
		for (list<CObj*>::iterator iter2 = pTemp2->begin(); iter2 != pTemp2->end(); ++iter2)
		{
			IntersectRect(&rcCol, &(*iter)->GetRect(), &(((CBox*)(*iter2))->GetBox()));

			LONG fLength = rcCol.right - rcCol.left;
			LONG fHeight = rcCol.bottom - rcCol.top;

			if (fLength > fHeight)			//상하충돌
			{
				if (rcCol.top == ((CBox*)(*iter2))->GetBox().top)	//상충돌
				{
					((CPlayer*)(*iter))->SetJump(false);
					(*iter)->SetPos((*iter)->GetInfo().fX, float(rcCol.top - 20));
				}
				else if (rcCol.bottom == ((CBox*)(*iter2))->GetBox().bottom)	//하충돌
				{
					((CPlayer*)(*iter))->SetJump(false);
					(*iter)->SetPos((*iter)->GetInfo().fX, float(rcCol.bottom + 20));
				}

			}
			else if (fLength < fHeight)		//좌우충돌
			{
				if (rcCol.left == ((CBox*)(*iter2))->GetBox().left)		// 좌충돌
				{
					(*iter)->SetPos(float(rcCol.left - 20), (*iter)->GetInfo().fY + 5);
				}
				else if (rcCol.right == ((CBox*)(*iter2))->GetBox().right)		// 우충돌
				{
					(*iter)->SetPos(float(rcCol.right + 20), (*iter)->GetInfo().fY + 5);
				}
			}
		}
	}
}

void CCollisionMgr::CollisionMap(list<CObj*>* pBullet, list<LINE*> pMap)	// 선충돌
{
	for(list<CObj*>::iterator iter = pBullet->begin(); iter != pBullet->end(); ++iter)
	{
		for(list<LINE*>::iterator iter2 = pMap.begin(); iter2 != pMap.end();)
		{
			if((*iter)->GetInfo().fY >= (*iter2)->tRPoint.fY)
			{		
				::Safe_Delete(*iter);
				iter = pBullet->erase(iter);
			}
			else
			{
				++iter2;
			}

			if(iter == pBullet->end())
			{
				break;
			}
		}

		if(iter == pBullet->end())
		{
			break;
		}
	}
}


void CCollisionMgr::CollisionItem(list<CObj*>* pItem, list<CObj*>* pPlayer)	//아이템충돌
{
	for(list<CObj*>::iterator iter = pItem->begin(); iter != pItem->end(); ++iter)
	{
		for(list<CObj*>::iterator iter2 = pPlayer->begin(); iter2 != pPlayer->end();)
		{
			float	fSum = ((*iter)->GetInfo().fCX / 2.f) + ((*iter2)->GetInfo().fCX / 2.f);
			float   fWidth = (*iter2)->GetInfo().fX - (*iter)->GetInfo().fX;
			float   fHeight = (*iter2)->GetInfo().fY - (*iter)->GetInfo().fY;
			float	fDistance = sqrt(fWidth * fWidth + fHeight * fHeight);

			if((fSum >= fDistance) && ((*iter))->GetType() == ITEM_ATTACK)
			{		
				(*iter2)->SetType(PLAYER_TANK);
				::Safe_Delete(*iter);
				iter = pItem->erase(iter);
			}
			else if((fSum >= fDistance) && ((*iter))->GetType() == ITEM_RECOVERY)
			{		
				(*iter2)->SetHP(20);
				::Safe_Delete(*iter);
				iter = pItem->erase(iter);
			}
			else
			{
				++iter2;
			}

			if(iter == pItem->end())
			{
				break;
			}
		}

		if(iter == pItem->end())
		{
			break;
		}
	}
}

void CCollisionMgr::CollisionBox2(list<CObj*>* pTemp, list<CObj*>* pTemp2)		// pTemp = 총알 , pTemp2 = 박스를 지정.
{
	RECT rcCol;

	for (list<CObj*>::iterator iter = pTemp->begin(); iter != pTemp->end(); ++iter) 
	{
		for (list<CObj*>::iterator iter2 = pTemp2->begin(); iter2 != pTemp2->end();)
		{
			IntersectRect(&rcCol, &(*iter)->GetRect(),  &(((CBox*)(*iter2))->GetBox()));

			float fLength = float(rcCol.right - rcCol.left);
			float fHeight = float(rcCol.bottom - rcCol.top);

			if (fLength > fHeight)			//상하충돌
			{
				if (rcCol.top == ((CBox*)(*iter2))->GetBox().top)	//상충돌
				{
					::Safe_Delete(*iter);
					iter = pTemp->erase(iter);
				}
				else if (rcCol.bottom == ((CBox*)(*iter2))->GetBox().bottom)	//하충돌
				{
					::Safe_Delete(*iter);
					iter = pTemp->erase(iter);
				}

			}
			else if (fLength < fHeight)		//좌우충돌
			{
				if (rcCol.left == ((CBox*)(*iter2))->GetBox().left)		// 좌충돌
				{
					::Safe_Delete(*iter);
					iter = pTemp->erase(iter);
				}
				else if (rcCol.right == ((CBox*)(*iter2))->GetBox().right)		// 우충돌
				{
					::Safe_Delete(*iter);
					iter = pTemp->erase(iter);
				}
			}

			else
			{
				++iter2;
			}
			if(iter == pTemp->end())
			{
				return;

			}
		}
		if(iter == pTemp->end())
		{
			return;
		}
	}
}
void CCollisionMgr::CollisionAttack(list<CObj*>* pTemp, list<CObj*>* pTemp2)		// pTemp = 불렛,몬스터불렛	pTemp2 = 플레이어,몬스터를 지정
{
	for(list<CObj*>::iterator iter = pTemp->begin();
		iter != pTemp->end();)
	{
		for(list<CObj*>::iterator iter2 = pTemp2->begin();
			iter2 != pTemp2->end();)
		{
			float	fSum = ((*iter)->GetInfo().fCX / 2.f) + ((*iter2)->GetInfo().fCX / 2.f);
			float   fWidth = (*iter2)->GetInfo().fX - (*iter)->GetInfo().fX;
			float   fHeight = (*iter2)->GetInfo().fY - (*iter)->GetInfo().fY;
			float	fDistance = sqrt(fWidth * fWidth + fHeight * fHeight);

			if(fSum >= fDistance)
			{		
				(*iter)->SetDamage((*iter2)->GetStat().fAttack);
				(*iter2)->SetDamage((*iter)->GetStat().fAttack);

				if ((*iter)->GetStat().fHp <= 0)
				{
					::Safe_Delete(*iter);
					iter = pTemp->erase(iter);
				}

				if ((*iter2)->GetStat().fHp <= 0)
				{
					::Safe_Delete(*iter2);
					iter2 = pTemp2->erase(iter2);

					if (iter2 == pTemp2->end())
					{
						break;
					}
				}
				if (iter == pTemp->end())
				{
					break;
				}
				else
				{
					++iter2;
				}

			}
			else
			{
				++iter2;
			}
		}
		if (iter == pTemp->end())
		{
			break;
		}
		else
		{
			++iter;
		}

	}

}

void CCollisionMgr::CollisionKinfe(list<CObj*>* pBullet, list<CObj*>* pPlayer)
{
	for(list<CObj*>::iterator iter = pBullet->begin(); iter != pBullet->end(); ++iter)
	{
		for(list<CObj*>::iterator iter2 = pPlayer->begin(); iter2 != pPlayer->end();)
		{
			if(((*iter)->GetInfo().fX >= (*iter2)->GetInfo().fX + 50) && 
				((*iter)->GetType() == BULLET_KNIFE))
			{		
				::Safe_Delete(*iter);
				iter = pBullet->erase(iter);
			}
			else if(((*iter)->GetInfo().fX <= (*iter2)->GetInfo().fX - 50) && 
				((*iter)->GetType() == BULLET_KNIFE))
			{		
				::Safe_Delete(*iter);
				iter = pBullet->erase(iter);
			}
			else
			{
				++iter2;
			}
				
			if(iter == pBullet->end())
			{
				break;
			}
		}

		if(iter == pBullet->end())
		{
			break;
		}
	}
}


void CCollisionMgr::CollisionWell(list<CObj*>* pPlayer)
{
	for(list<CObj*>::iterator iter = pPlayer->begin(); iter != pPlayer->end(); ++iter)
	{
		if((*iter)->GetInfo().fY <= 10)
		{		
			(*iter)->SetPos((*iter)->GetInfo().fX ,10.f);
		}
	}	
}

void	CCollisionMgr::CollisionMonster(list<CObj*>* pPlayer, list<CObj*>* pMonster)
{
	RECT rcCol;

	for (list<CObj*>::iterator iter = pPlayer->begin(); iter != pPlayer->end(); )
	{
		for (list<CObj*>::iterator iter2 = pMonster->begin(); iter2 != pMonster->end(); )
		{
			IntersectRect(&rcCol, &(*iter)->GetRect(), &(*iter2)->GetRect());

			float fLength = float(rcCol.right - rcCol.left);
			float fHeight = float(rcCol.bottom - rcCol.top);

			if (fLength > fHeight)			//상하충돌
			{
				if ((*iter)->GetInfo().fY <= (*iter2)->GetRect().top)	//상충돌
				{
					(*iter2)->SetDamage((*iter)->GetStat().fAttack);

					if((*iter2)->GetType() == MONSTER_3)
					{
						(*iter)->SetDamage((*iter2)->GetStat().fAttack);
					}

					(*iter)->SetPos((*iter)->GetInfo().fX, float((*iter2)->GetRect().top - 20));
					((CPlayer*)(*iter))->SetJump(false);

					if ((*iter)->GetStat().fHp <= 0)
					{
						::Safe_Delete(*iter);
						iter = pPlayer->erase(iter);
					}
					if ((*iter2)->GetStat().fHp <= 0)
					{
						::Safe_Delete(*iter2);
						iter2 = pMonster->erase(iter2);
					}
					else
						++iter2;
				}
				else											//하충돌
				{
					(*iter)->SetDamage((*iter2)->GetStat().fAttack);
					if((*iter2)->GetType() == MONSTER_1)
					{
						(*iter)->SetPos((*iter)->GetInfo().fX, float((*iter2)->GetRect().bottom + 25));
					}
					else
						(*iter2)->SetDamage((*iter)->GetStat().fAttack);
					
					((CPlayer*)(*iter))->SetJump(false);

					if ((*iter)->GetStat().fHp <= 0)
					{
						::Safe_Delete(*iter);
						iter = pPlayer->erase(iter);
					}
					if ((*iter2)->GetStat().fHp <= 0)
					{
						::Safe_Delete(*iter2);
						iter2 = pMonster->erase(iter2);
					}
					else
						++iter2;
				}
			}
			else if (fLength < fHeight)
			{
				if ((*iter)->GetInfo().fX <= (*iter2)->GetInfo().fX)	//좌충돌
				{
					(*iter)->SetDamage((*iter2)->GetStat().fAttack);
					if((*iter2)->GetType() != MONSTER_2)
					{
						(*iter)->SetPos(float((*iter2)->GetRect().left - 20), (*iter)->GetInfo().fY);
					}
					else
						(*iter2)->SetDamage((*iter)->GetStat().fAttack);
					

					if ((*iter)->GetStat().fHp <= 0)
					{
						::Safe_Delete(*iter);
						iter = pPlayer->erase(iter);
					}
					if ((*iter2)->GetStat().fHp <= 0)
					{
						::Safe_Delete(*iter2);
						iter2 = pMonster->erase(iter2);
					}

					else
						++iter2;
				}
				else												//우충돌
				{
					(*iter)->SetDamage((*iter2)->GetStat().fAttack);
					if((*iter2)->GetType() != MONSTER_2)
					{
						(*iter)->SetPos(float((*iter2)->GetRect().right + 8), (*iter)->GetInfo().fY - 3);
					}
					else
						(*iter2)->SetDamage((*iter)->GetStat().fAttack);

					if ((*iter)->GetStat().fHp <= 0)
					{
						::Safe_Delete(*iter);
						iter = pPlayer->erase(iter);
					}
					if ((*iter2)->GetStat().fHp <= 0)
					{
						::Safe_Delete(*iter2);
						iter2 = pMonster->erase(iter2);
					}
					else
						++iter2;
				}

			}
			else
				++iter2;
			if (iter == pPlayer->end())
				return;
		}
		if (iter == pPlayer->end())
			return;
		else 
			++iter;

	}
}

//////////////////
void	CCollisionMgr::CollisionBoss(list<CObj*>* pPlayer, list<CObj*>* pBoss)
{
	RECT rcCol;

	for (list<CObj*>::iterator iter = pPlayer->begin(); iter != pPlayer->end(); )
	{
		for (list<CObj*>::iterator iter2 = pBoss->begin(); iter2 != pBoss->end(); )
		{
			IntersectRect(&rcCol, &(*iter)->GetRect(), &(*iter2)->GetRect());

			float fLength = float(rcCol.right - rcCol.left);
			float fHeight = float(rcCol.bottom - rcCol.top);

			if (fLength > fHeight)			//상하충돌
			{
				if ((*iter)->GetInfo().fY <= (*iter2)->GetRect().top)	//상충돌
				{
					(*iter)->SetPos((*iter)->GetInfo().fX, float((*iter2)->GetRect().top - 20));
					((CPlayer*)(*iter))->SetJump(false);

					if ((*iter2)->GetStat().fHp <= 0)
					{
						::Safe_Delete(*iter2);
						iter = pBoss->erase(iter2);
					}

					else
						++iter2;
				}
				else											//하충돌
				{
					(*iter)->SetPos((*iter)->GetInfo().fX, float((*iter2)->GetRect().bottom + 25));					
					((CPlayer*)(*iter))->SetJump(false);

					if ((*iter2)->GetStat().fHp <= 0)
					{
						::Safe_Delete(*iter2);
						iter = pBoss->erase(iter2);
					}

					else
						++iter2;
				}
			}
			else if (fLength < fHeight)
			{
				if ((*iter)->GetInfo().fX <= (*iter2)->GetInfo().fX)	//좌충돌
				{
					(*iter)->SetPos(float((*iter2)->GetRect().left - 20), (*iter)->GetInfo().fY);

					if ((*iter2)->GetStat().fHp <= 0)
					{
						::Safe_Delete(*iter2);
						iter2 = pBoss->erase(iter2);
					}

					else
						++iter2;
				}
				else												//우충돌
				{
					(*iter)->SetPos(float((*iter2)->GetRect().right + 15), (*iter)->GetInfo().fY - 3);

					if ((*iter2)->GetStat().fHp <= 0)
					{
						::Safe_Delete(*iter2);
						iter2 = pBoss->erase(iter2);
					}
					else
						++iter2;
				}

			}
			else
				++iter2;
			if (iter == pPlayer->end())
				return;
		}
		if (iter == pPlayer->end())
			return;
		else 
			++iter;

	}
}