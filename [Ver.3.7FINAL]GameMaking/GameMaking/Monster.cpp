#include "StdAfx.h"
#include "Monster.h"
#include "AbstractFactory.h"

CMonster::CMonster(void)
{
}

CMonster::CMonster(int _iInput)
: m_iType(_iInput)
{
}


CMonster::~CMonster(void)
{
	Release();
}

void CMonster::Initialize(void)	
{
	m_iCollision = 0;
	m_Timer.SetTimer();
	switch (m_iType)
	{
	case 1:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 60.f, 60.f);
		m_tStat = STAT(1.f, 1.f, 1.f, 6.f);
		break;
	case 2:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 1.f, 6.f);
		break;
	case 3:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 1.f, 15.f);
		break;
	case 4:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 1.f, 15.f);
		break;
	case 5:		// 중보
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 50.f, 50.f);
		m_tStat = STAT(30.f, 30.f, 5.f, 13.f);
		break;
	case 6:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 70.f, 70.f);
		m_tStat = STAT(50.f, 50.f, 5.f, 20.f);
		break;
	}	
}

void CMonster::Progress(float _Time)
{
	if (m_tInfo.fY > WINCY - 10 || m_tInfo.fX <= 170 || m_tInfo.fX >= WINCX + 50)
	{
		SetDestroy();
	}

	if (m_tInfo.fX > WINCX - 10 || m_tInfo.fX < 160)
	{
		m_tStat.fSpeed *= -1;
	}

	if ((m_Timer.RemainTime[0] -= _Time) <= 0)
	{
		switch (m_iType)
		{
		case 1:		// 수직 낙하
			m_tInfo.fY += m_tStat.fSpeed;
			m_Timer.RemainTime[0] = 50;
			break;

		case 2:		// 좌우 왕복
			m_tInfo.fX += m_tStat.fSpeed;
			if (m_tInfo.fX <= 170.f || m_tInfo.fX > (float)WINCX - 20)
			{
				m_tStat.fSpeed *= -1;
			}
			break;

		case 3:		// 우측 대각선
			m_tInfo.fX += m_tStat.fSpeed / 2;
			m_tInfo.fY += m_tStat.fSpeed / 4;
			m_Timer.RemainTime[0] = 50;
			break;

		case 4:		// 좌측 대각선
			m_tInfo.fX -= m_tStat.fSpeed / 2;
			m_tInfo.fY += m_tStat.fSpeed / 4;
			m_Timer.RemainTime[0] = 50;
			break;
		case 5:		// 중간보스
			if(m_iCollision == 0)
			{
				m_tInfo.fX -= m_tStat.fSpeed / 2;
				m_tInfo.fY += m_tStat.fSpeed / 15;

				if (m_tInfo.fX <= 200.f)
				{
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY- 20, 4))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY- 30, 4))));
					m_tInfo.fX += m_tStat.fSpeed / 2;
					m_tInfo.fY += m_tStat.fSpeed / 15;

					m_iCollision = 1;
				}
			}

			if(m_iCollision == 1)
			{
				m_tInfo.fX += m_tStat.fSpeed / 2;
				m_tInfo.fY += m_tStat.fSpeed / 15;

				if (m_tInfo.fX >= 750.f)
				{
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY- 20, 4))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY- 30, 4))));
					m_tInfo.fX -= m_tStat.fSpeed / 2;
					m_tInfo.fY += m_tStat.fSpeed / 15;

					m_iCollision = 2;
				}
			}

			if(m_iCollision == 2)
			{
				m_tInfo.fX -= m_tStat.fSpeed / 2;
				m_tInfo.fY += m_tStat.fSpeed / 15;

				if (m_tInfo.fX <= 200.f)
				{
					m_iCollision = 0;
				}
			}

			if(m_tInfo.fY >= 250)
			{
				m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX - 50, m_tInfo.fY, 3))));
				m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX + 50, m_tInfo.fY, 3))));
				m_tInfo.fX = rand() % 550 + 200;
				m_tInfo.fY = 50;

				m_iCollision = 0;
			}
			break;
		case 6:
			switch (m_iCollision)
			{
			case 0:
				m_tInfo.fY += m_tStat.fSpeed;
				if (m_tInfo.fY >= 100)
				{
					++m_iCollision;
				}
				break;
			case 1:
				m_tInfo.fX += m_tStat.fSpeed;
				if (m_tInfo.fX <= 200.f || m_tInfo.fX > (float)WINCX - 20)
				{
					m_tStat.fSpeed *= -1;
				}
				if (m_tStat.fHp <= m_tStat.fFullHp / 2)
				{
					++m_iCollision;
				}
				break;
			case 2:
				if ((m_Timer.RemainTime[2] -= _Time) <= 0)
				{
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX-200, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX-140, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX-80, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX-20, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX+20, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX+80, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX+140, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX+200, m_tInfo.fY, 1))));
					m_Timer.RemainTime[2] = 2000;
					++m_iCollision;
				}
				break;
			case 3:
				m_tInfo.fX += m_tStat.fSpeed;
				if (m_tInfo.fX <= 200.f || m_tInfo.fX > (float)WINCX - 20)
				{
					m_tStat.fSpeed *= -1;
				}
				if ((m_Timer.RemainTime[2] -= _Time) <= 0)
				{
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX-200, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX-140, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX-80, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX-20, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX+20, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX+80, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX+140, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX+200, m_tInfo.fY, 1))));
					m_Timer.RemainTime[2] = 2000;
					++m_iCollision;
				}
				break;
				case 4:
				m_tInfo.fX += m_tStat.fSpeed;
				if (m_tInfo.fX <= 200.f || m_tInfo.fX > (float)WINCX - 20)
				{
					m_tStat.fSpeed *= -1;
				}
				if ((m_Timer.RemainTime[2] -= _Time) <= 0)
				{
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, 4))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, 4))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, 4))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, 4))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX-200, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX-140, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX-80, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX-20, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX+20, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX+80, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX+140, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX+200, m_tInfo.fY, 1))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY- 20, 2))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY- 30, 2))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY- 40, 2))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX-40, m_tInfo.fY, 3))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, 3))));
					m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX+40, m_tInfo.fY, 3))));
					m_Timer.RemainTime[2] = 2000;
					break;
				}
			}
		}
	}
	if ((m_Timer.RemainTime[1] -= _Time) <= 0)
	{
		m_pMonBullet->push_back(((CAbstractFactory<CMonBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, 1))));
		m_Timer.RemainTime[1] = 700	;
	}
}

void CMonster::Render(HDC hdc)
{
	switch (m_iType)
	{
	case 1:
		Rectangle(hdc,
		int(m_tInfo.fX - 10 / 2.f),
		int(m_tInfo.fY - 10),
		int(m_tInfo.fX + 10 / 2.f),
		int(m_tInfo.fY + 30)
		);

		Rectangle(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - 10),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY + 10)
		);
		break;
		
	case 2:
		Rectangle(hdc,
		int(m_tInfo.fX - 10 / 2.f),
		int(m_tInfo.fY - 10),
		int(m_tInfo.fX + 10 / 2.f),
		int(m_tInfo.fY + 30)
		);

		Rectangle(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - 10),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY + 10)
		);
		break;
		
	case 3:
		Rectangle(hdc,
		int(m_tInfo.fX - 10 / 2.f),
		int(m_tInfo.fY - 10),
		int(m_tInfo.fX + 10 / 2.f),
		int(m_tInfo.fY + 30)
		);

		Rectangle(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - 10),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY + 10)
		);
		break;
		
	case 4:
		Rectangle(hdc,
		int(m_tInfo.fX - 10 / 2.f),
		int(m_tInfo.fY - 10),
		int(m_tInfo.fX + 10 / 2.f),
		int(m_tInfo.fY + 30)
		);

		Rectangle(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - 10),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY + 10)
		);
		break;
		
	case 5:
		Rectangle(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fX + m_tInfo.fCX / 2.f),
			int(m_tInfo.fY + m_tInfo.fCY / 2.f)
		);

		Ellipse(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f / 2.f),
			int(m_tInfo.fX),
			int(m_tInfo.fY + m_tInfo.fCY / 2.f / 2.f)
		);

		Ellipse(hdc,
			int(m_tInfo.fX),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f / 2.f),
			int(m_tInfo.fX + m_tInfo.fCX / 2.f),
			int(m_tInfo.fY + m_tInfo.fCY / 2.f / 2.f)
		);

		Rectangle(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f),
			int(m_tInfo.fY + m_tInfo.fCY / 3.f),
			int(m_tInfo.fX + m_tInfo.fCX / 2.f),
			int(m_tInfo.fY + m_tInfo.fCY / 2.f)
		);

		Rectangle(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 4.f),
			int(m_tInfo.fY + m_tInfo.fCY / 3.f),
			int(m_tInfo.fX + m_tInfo.fCX / 4.f),
			int(m_tInfo.fY + m_tInfo.fCY / 2.f)
		);
		break;
		
	case 6:
	Ellipse(hdc,
	int(m_tInfo.fX - m_tInfo.fCX / 2.f),
	int(m_tInfo.fY - m_tInfo.fCY / 2.f),
	int(m_tInfo.fX + m_tInfo.fCX / 2.f),
	int(m_tInfo.fY + m_tInfo.fCY / 2.f)
	);

	Ellipse(hdc,
	int(m_tInfo.fX - m_tInfo.fCX / 2.f),
	int(m_tInfo.fY - m_tInfo.fCY / 2.f),
	int(m_tInfo.fX + m_tInfo.fCX / 2.f),
	int(m_tInfo.fY + m_tInfo.fCY / 2.f)
	);

	Ellipse(hdc,
	int(m_tInfo.fX - m_tInfo.fCX / 2.f),
	int(m_tInfo.fY - m_tInfo.fCY / 7.f),
	int(m_tInfo.fX + m_tInfo.fCX / 2.f),
	int(m_tInfo.fY + m_tInfo.fCY / 7.f)
	);
		
	Ellipse(hdc,
	int(m_tInfo.fX - m_tInfo.fCX / 7.f),
	int(m_tInfo.fY - m_tInfo.fCY / 7.f),
	int(m_tInfo.fX + m_tInfo.fCX / 7.f),
	int(m_tInfo.fY + m_tInfo.fCY / 7.f)
	);
		break;
	}
}

void CMonster::Release(void)
{
}



void CMonster::SetMonBullet(list<CObj*>* _pMonBullet)
{
	m_pMonBullet = _pMonBullet;
}
