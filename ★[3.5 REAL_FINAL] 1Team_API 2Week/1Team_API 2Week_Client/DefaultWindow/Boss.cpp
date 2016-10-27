#include "StdAfx.h"
#include "Boss.h"
#include "ObjFactory.h"
#include "MonsterBullet.h"

CBoss::CBoss(void)
{
}

CBoss::CBoss(int _iType)
{
	m_iType = _iType;
	m_fAngle = 0.f;
}

CBoss::~CBoss(void)
{
}

void CBoss::Initialize(void)
{
	m_CTimer.SetTimer();

	m_fSpeed = 5.f;
	switch (m_iType)
	{
	case BOSS_1:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 200.f, 100.f);
		m_tStat = STAT(20.f, 1.f, 10.f);
		break;
	case BOSS_2:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 150.f, 150.f);
		m_tStat = STAT(10.f, 1.f, 0.f);
		break;
	case BOSS_3:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	}
}

void CBoss::Progress(float _fTime)
{
	m_fAngle += 5.f;

	switch (m_iType)
	{
	case BOSS_1:
			m_tInfo.fX += m_fSpeed;

			if(m_tInfo.fX <= 3300.f || 3800.f <= m_tInfo.fX)
			{
				m_fSpeed *= -1.f;
			}

			if((m_CTimer.m_fRemainTime[0] -= _fTime) <=0 ) //·£´ýÀ¸·Î ½Ã°£¹Þ¾Æ¿Í¼­ ÃÑ¾Ë ½î±â
			{
				m_pMBulletList->push_back(CObjFactory<CMonsterBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, BULLET_BOSS_11));
				m_pMBulletList->push_back(CObjFactory<CMonsterBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, BULLET_BOSS_12));
				m_pMBulletList->push_back(CObjFactory<CMonsterBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, BULLET_BOSS_13));
				m_CTimer.m_fRemainTime[0] = 200;
			}
			break;
	case BOSS_2:
			m_tInfo.fX += 0.5f*m_fSpeed;
			if(m_tInfo.fX <= 3600.f || 3800.f <= m_tInfo.fX)
			{
				m_fSpeed *= -1.f;
			}
			if( true ) //·£´ýÀ¸·Î ½Ã°£¹Þ¾Æ¿Í¼­ ÃÑ¾Ë ½î±â
			{
				m_pMBulletList->push_back(CObjFactory<CMonsterBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, BULLET_BOSS_2,m_fAngle));
			}
			break;
	case BOSS_3:
			break;
	}
}

void CBoss::Render(HDC hdc)
{
	switch (m_iType)
	{
	case BOSS_1:
		Rectangle(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		MoveToEx(hdc, (int)(m_tInfo.fX - 50 + m_fScrollX), (int)m_tInfo.fY - 25, NULL);
		LineTo(hdc, (int)(m_tInfo.fX - 50 + m_fScrollX), (int)m_tInfo.fY - 20);
		LineTo(hdc, (int)(m_tInfo.fX - 40 + m_fScrollX), (int)m_tInfo.fY - 20);
		LineTo(hdc, (int)(m_tInfo.fX - 40 + m_fScrollX), (int)m_tInfo.fY - 25);
		LineTo(hdc, (int)(m_tInfo.fX - 50 + m_fScrollX), (int)m_tInfo.fY - 25);
		MoveToEx(hdc, (int)(m_tInfo.fX + 50 + m_fScrollX), (int)m_tInfo.fY - 25, NULL);
		LineTo(hdc, (int)(m_tInfo.fX + 50 + m_fScrollX), (int)m_tInfo.fY - 20);
		LineTo(hdc, (int)(m_tInfo.fX + 40 + m_fScrollX), (int)m_tInfo.fY - 20);
		LineTo(hdc, (int)(m_tInfo.fX + 40 + m_fScrollX), (int)m_tInfo.fY - 25);
		LineTo(hdc, (int)(m_tInfo.fX + 50 + m_fScrollX), (int)m_tInfo.fY - 25);
		MoveToEx(hdc, (int)(m_tInfo.fX - 50 + m_fScrollX), (int)m_tInfo.fY + 50, NULL);
		LineTo(hdc, (int)(m_tInfo.fX - 50 + m_fScrollX), (int)m_tInfo.fY + 10);
		LineTo(hdc, (int)(m_tInfo.fX + 50 + m_fScrollX), (int)m_tInfo.fY + 10);
		LineTo(hdc, (int)(m_tInfo.fX + 50 + m_fScrollX), (int)m_tInfo.fY + 50);
		MoveToEx(hdc, (int)(m_tInfo.fX - 30 + m_fScrollX), (int)m_tInfo.fY + 50, NULL);
		LineTo(hdc, (int)(m_tInfo.fX - 30 + m_fScrollX), (int)m_tInfo.fY + 10);
		MoveToEx(hdc, (int)(m_tInfo.fX - 10 + m_fScrollX), (int)m_tInfo.fY + 50, NULL);
		LineTo(hdc, (int)(m_tInfo.fX - 10 + m_fScrollX), (int)m_tInfo.fY + 10);
		MoveToEx(hdc, (int)(m_tInfo.fX + 10 + m_fScrollX), (int)m_tInfo.fY + 50, NULL);
		LineTo(hdc, (int)(m_tInfo.fX + 10 + m_fScrollX), (int)m_tInfo.fY + 10);
		MoveToEx(hdc, (int)(m_tInfo.fX + 30 + m_fScrollX), (int)m_tInfo.fY + 50, NULL);
		LineTo(hdc, (int)(m_tInfo.fX + 30 + m_fScrollX), (int)m_tInfo.fY + 10);
		break;
	case BOSS_2:
		Ellipse(hdc,
			int(m_tInfo.fX - 75 + m_fScrollX),
			int(m_tInfo.fY - 75),
			int(m_tInfo.fX - 40 + m_fScrollX),
			int(m_tInfo.fY - 40));
		Ellipse(hdc,
			int(m_tInfo.fX + 75 + m_fScrollX),
			int(m_tInfo.fY - 75),
			int(m_tInfo.fX + 40 + m_fScrollX),
			int(m_tInfo.fY - 40));
		Ellipse(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		MoveToEx(hdc, (int)(m_tInfo.fX - 40 + m_fScrollX), (int)m_tInfo.fY - 30, NULL);
		LineTo(hdc, (int)(m_tInfo.fX - 40 + m_fScrollX), (int)m_tInfo.fY - 20);
		LineTo(hdc, (int)(m_tInfo.fX - 20 + m_fScrollX), (int)m_tInfo.fY - 20);
		LineTo(hdc, (int)(m_tInfo.fX - 20 + m_fScrollX), (int)m_tInfo.fY - 30);
		LineTo(hdc, (int)(m_tInfo.fX - 40 + m_fScrollX), (int)m_tInfo.fY - 30);
		MoveToEx(hdc, (int)(m_tInfo.fX + 40 + m_fScrollX), (int)m_tInfo.fY - 30, NULL);
		LineTo(hdc, (int)(m_tInfo.fX + 40 + m_fScrollX), (int)m_tInfo.fY - 20);
		LineTo(hdc, (int)(m_tInfo.fX + 20 + m_fScrollX), (int)m_tInfo.fY - 20);
		LineTo(hdc, (int)(m_tInfo.fX + 20 + m_fScrollX), (int)m_tInfo.fY - 30);
		LineTo(hdc, (int)(m_tInfo.fX + 40 + m_fScrollX), (int)m_tInfo.fY - 30);
		MoveToEx(hdc, (int)(m_tInfo.fX - 40 + m_fScrollX), (int)m_tInfo.fY + 30, NULL);
		LineTo(hdc, (int)(m_tInfo.fX - 40 + m_fScrollX), (int)m_tInfo.fY + 15);
		LineTo(hdc, (int)(m_tInfo.fX + 40 + m_fScrollX), (int)m_tInfo.fY + 15);
		LineTo(hdc, (int)(m_tInfo.fX + 40 + m_fScrollX), (int)m_tInfo.fY + 30);
		LineTo(hdc, (int)(m_tInfo.fX - 40 + m_fScrollX), (int)m_tInfo.fY + 30);
		MoveToEx(hdc, (int)(m_tInfo.fX - 20 + m_fScrollX), (int)m_tInfo.fY + 30, NULL);
		LineTo(hdc, (int)(m_tInfo.fX - 20 + m_fScrollX), (int)m_tInfo.fY + 15);
		MoveToEx(hdc, (int)(m_tInfo.fX + m_fScrollX), (int)m_tInfo.fY + 30, NULL);
		LineTo(hdc, (int)(m_tInfo.fX + m_fScrollX), (int)m_tInfo.fY + 15);
		MoveToEx(hdc, (int)(m_tInfo.fX + 20 + m_fScrollX), (int)m_tInfo.fY + 30, NULL);
		LineTo(hdc, (int)(m_tInfo.fX + 20 + m_fScrollX), (int)m_tInfo.fY + 15);
		break;
	}
}

void CBoss::Release(void)
{
}

void	CBoss::SetMBulletList	(list<CObj*>* _pMBulletList)
{
	m_pMBulletList = _pMBulletList;
}