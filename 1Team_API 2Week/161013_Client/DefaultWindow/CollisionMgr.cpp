#include "StdAfx.h"
#include "CollisionMgr.h"

CCollisionMgr::CCollisionMgr(void)
{
}

CCollisionMgr::~CCollisionMgr(void)
{
}

void CCollisionMgr::CollisionSphere(list<CObj*>* pTemp, list<CObj*>* pTemp2)
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