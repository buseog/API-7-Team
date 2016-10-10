
#include "StdAfx.h"
#include "Stage3.h"
#include "Player.h"
#include "AbstractFactory.h"

CStage3::CStage3(void)
{
}

CStage3::~CStage3(void)
{
	Release();
}

void CStage3::Initialize(void)
{
	m_Timer.SetTimer();
	iWave = 0;
	m_hdc = GetDC(g_hWnd);
	srand(unsigned(time(NULL)));
}

void CStage3::Progress(float _Time)
{
	//일반 몬스터
	if ((m_Timer.RemainTime[2] -= _Time) <= 0)		//	1번 Wave (1, 3타입 몬스터 출몰)
	{
		if (iWave < 5 )
		{
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(300, 20, 1));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(170, 30, 3));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);
			
			++iWave;
			m_Timer.RemainTime[2] = 2000;
		}
	}

	if ((m_Timer.RemainTime[1] -= _Time) <= 0)		// 휴식 5초
	{
		if (iWave >= 5 && iWave < 10)
		{
			++iWave;
			m_Timer.RemainTime[1] = 1000;
		}
	}


	if ((m_Timer.RemainTime[2] -= _Time) <= 0)		// 2번 Wave (2, 4타입 몬스터 출몰)
	{
		if (iWave >= 10 && iWave < 15)
		{
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(450, 70, 2));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(740, 40, 4));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);

			++iWave;
			m_Timer.RemainTime[2] = 2000;
		}
	}


	if ((m_Timer.RemainTime[1] -= _Time) <= 0)		// 휴식 5초
	{
		if (iWave >= 15 && iWave < 20)
		{
			++iWave;
			m_Timer.RemainTime[1] = 1000;
		}
	}

	// 중간 보스 몬스터 


	if ((m_Timer.RemainTime[2] -= _Time) <= 0)		// 3번 Wave (5 타입, 1, 2타입 몬스터 출몰)
	{
		if (iWave >= 20 && iWave < 30)
		{
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(400, 80, 1));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(500, 80, 2));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(400, 100, 5));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);

			++iWave;
			m_Timer.RemainTime[2] = 2000;
		}
	}

	if ((m_Timer.RemainTime[1] -= _Time) <= 0)		// 휴식 5초
	{
		if (iWave >= 30 && iWave < 35)
		{
			++iWave;
			m_Timer.RemainTime[1] = 1000;
		}
	}

	if ((m_Timer.RemainTime[2] -= _Time) <= 0)		// 4번 Wave (3, 4타입 몬스터 출몰)
	{
		if (iWave >= 35 && iWave < 40)
		{
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(300, 20, 3));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(600, 50, 4));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);

			++iWave;
			m_Timer.RemainTime[2] = 2000;
		}
	}

	if ((m_Timer.RemainTime[1] -= _Time) <= 0)		// 휴식 5초
	{
		if (iWave >= 40 && iWave < 45)
		{
			++iWave;
			m_Timer.RemainTime[1] = 1000;
		}
	}


	// 최종 보스 몬스터

	if ((m_Timer.RemainTime[2] -= _Time) <= 0)		// 최종 Wave (6타입 1,2,3,4타입 몬스터 출몰)
	{
		if (iWave >= 45 && iWave < 50)
		{
	   		m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj((rand() % 550) + 200, -10, 1));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(300, 50, 2));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj((rand() % 550) + 200, 10, 3));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);
			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj(600, 50, 4));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);

			m_ListObj[OBJ_MONSTER]->push_back(CAbstractFactory<CMonster>::CreateObj((rand() % 550) + 200, -10, 6));
			((CMonster*)m_ListObj[OBJ_MONSTER]->back())->SetMonBullet(m_ListObj[OBJ_MONBULLET]);

			++iWave;
			m_Timer.RemainTime[2] = 2000;
		}
	}
	
	if (m_ListObj[OBJ_MONSTER]->empty())
	{
		if (iWave == 50)
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
void CStage3::Render(void)
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
void CStage3::Release(void)
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

void CStage3::SetListObj(int _iNum, list<CObj*>* _pListObj)
{
	m_ListObj[_iNum] = _pListObj;
}

int CStage3::Clear(void)
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