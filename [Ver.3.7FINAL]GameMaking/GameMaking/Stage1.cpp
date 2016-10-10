#include "StdAfx.h"
#include "Stage1.h"
#include "Player.h"
#include "AbstractFactory.h"

CStage1::CStage1(void)
{
}

CStage1::~CStage1(void)
{
	Release();
}

void CStage1::Initialize(void)
{
	srand(unsigned(time(NULL)));

	m_Timer.SetTimer();
	iWave = 0;
	m_hdc = GetDC(g_hWnd);		
}

void CStage1::Progress(float _Time)
{
	if ((m_Timer.RemainTime[2] -= _Time) <= 0)		// 1¹ø Wave
	{
		if (iWave < 5) 
		{
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(200, 100, 2));	
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);			

			++iWave;
			m_Timer.RemainTime[2] = 2000;
		}
	}

	if ((m_Timer.RemainTime[1] -= _Time) <= 0)		// ÈÞ½Ä(10ÃÊ)
	{
		if (iWave >= 5 && iWave < 15)
		{
			++iWave;
			m_Timer.RemainTime[1] = 1000;
		}
	}

	if ((m_Timer.RemainTime[2] -= _Time) <= 0)		// 2¹ø Wave
	{
		if (iWave >= 15 && iWave < 25)
		{
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj( (rand() % 550 + 200), 10, 1  ));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);			

			++iWave;
			m_Timer.RemainTime[2] = 2000;
		}
	}

	if ((m_Timer.RemainTime[1] -= _Time) <= 0)		// ÈÞ½Ä(10ÃÊ)
	{
		if (iWave >= 25 && iWave < 35)
		{
			++iWave;
			m_Timer.RemainTime[1] = 1000;
		}
	}

	if ((m_Timer.RemainTime[2] -= _Time) <= 0)		// 3¹ø Waves
	{
		if (iWave >= 35 && iWave < 45)
		{
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(200, 50, 3));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);

			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(750, 50, 4));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);

			++iWave;
			m_Timer.RemainTime[2] = 2000;
		}
	}

	if ((m_Timer.RemainTime[1] -= _Time) <= 0)		// ÈÞ½Ä(10ÃÊ)		
	{
		if (iWave >= 45 && iWave < 55)
		{
			++iWave;
			m_Timer.RemainTime[1] = 1000;
		}
	}

	if ((m_Timer.RemainTime[1] -= _Time) <= 0)		// Áß°£º¸½º			
	{
		if (iWave == 55)
		{
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(WINCX / 2, 50, 5));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);
			++iWave;
		}
	}

	if (m_ListObj[OBJ_MONSTER]->empty())
	{
		if (iWave == 56)
		{
			++iWave;
		}
	}

	if ((m_Timer.RemainTime[7] -= _Time) <= 0)	
	{
		if (iWave == 57 )
		{
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(350, -10, 6));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);
			++iWave;
		}
	}

	if (m_ListObj[OBJ_MONSTER]->empty())
	{
		if (iWave == 58)
		{
			iWave = 100;
		}
	}



	for (int i = 0; i < OBJ_END; ++i)
	{
		for (list<CObj*>::iterator Iter = m_ListObj[i]->begin(); Iter != m_ListObj[i]->end(); )
		{
			(*Iter)->Progress(_Time);
				
			if ((*Iter)->GetStat().Destroy == TRUE)
			{
				::Safe_Delete(*Iter);
				Iter = m_ListObj[i]->erase(Iter);
			}
			else
			{
				++Iter;
			}
		}
	}

	CCollisionMgr::CollisionSphere(m_ListObj[OBJ_BULLET], m_ListObj[OBJ_MONSTER]);
	CCollisionMgr::CollisionSphere(m_ListObj[OBJ_MONBULLET], m_ListObj[OBJ_PLAYER]);
	CCollisionMgr::CollisionSphere(m_ListObj[OBJ_MONBULLET], m_ListObj[OBJ_BULLET]);
}



void CStage1::Render(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (list<CObj*>::iterator Iter = m_ListObj[i]->begin(); Iter != m_ListObj[i]->end(); ++Iter)
		{
			(*Iter)->Render(m_hdc);

			if(m_ListObj[i] == m_ListObj[0])
			{
				(*Iter)->StatRender();
			}
		}
	}

}	
void CStage1::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (list<CObj*>::iterator Iter = m_ListObj[i]->begin(); Iter != m_ListObj[i]->end(); ++Iter)
		{
			(*Iter) = NULL;
		};
	}
	ReleaseDC(g_hWnd, m_hdc);
}

void CStage1::SetListObj(int _iNum, list<CObj*>* _pListObj)
{
	m_ListObj[_iNum] = _pListObj;
}

int CStage1::Clear(void)
{
	if (iWave == 100)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}