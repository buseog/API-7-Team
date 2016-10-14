#include "StdAfx.h"
#include "CollisionMgr.h"
#include "Player.h"

CCollisionMgr::CCollisionMgr(void)
{
}

CCollisionMgr::~CCollisionMgr(void)
{
}

void CCollisionMgr::CollisionSphere(list<CObj*>* pTemp, list<CObj*>* pTemp2)		// pTemp = �ҷ�,���ͺҷ�	pTemp2 = �÷��̾�,���͸� ����
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

void CCollisionMgr::CollisionBox(list<CObj*>* pTemp, list<CObj*>* pTemp2)		// pTemp = �÷��̾� , pTemp2 = �ڽ��� ����.
{
	RECT rcCol;

	for (list<CObj*>::iterator iter = pTemp->begin(); iter != pTemp->end(); ++iter)
	{
		for (list<CObj*>::iterator iter2 = pTemp2->begin(); iter2 != pTemp2->end(); ++iter2)
		{
			IntersectRect(&rcCol, &(*iter)->GetRect(), &(*iter2)->GetRect());

			float fLength = rcCol.right - rcCol.left;
			float fHeight = rcCol.bottom - rcCol.top;

			if (fLength > fHeight)			//�����浹
			{
				if (rcCol.top == (*iter2)->GetRect().top)	//���浹
				{
					((CPlayer*)(*iter))->SetJumpOff();
					(*iter)->SetPos((*iter)->GetInfo().fX, rcCol.top - 20);
				}
				else if (rcCol.bottom == (*iter2)->GetRect().bottom)	//���浹
				{
					((CPlayer*)(*iter))->SetJumpOff();
					(*iter)->SetPos((*iter)->GetInfo().fX, rcCol.bottom + 20);
				}

			}
			else if (fLength < fHeight)		//�¿��浹
			{
				if (rcCol.left == (*iter2)->GetRect().left)		// ���浹
				{
					((CPlayer*)(*iter))->SetJumpOff();
					(*iter)->SetPos(rcCol.left - 20, (*iter)->GetInfo().fY);
				}
				else if (rcCol.right == (*iter2)->GetRect().right)		// ���浹
				{
					((CPlayer*)(*iter))->SetJumpOff();
					(*iter)->SetPos(rcCol.right + 20, (*iter)->GetInfo().fY);
				}
			}
		}
	}
}