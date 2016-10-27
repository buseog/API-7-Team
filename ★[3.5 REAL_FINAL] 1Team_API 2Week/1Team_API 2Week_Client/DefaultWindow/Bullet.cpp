#include "StdAfx.h"
#include "Bullet.h"

CBullet::CBullet(void)
{
}

CBullet::CBullet(int _iType)
{
	m_iType = _iType;
}

CBullet::~CBullet(void)
{
}

void CBullet::Initialize(void)
{
	m_CTimer.SetTimer();


	switch (m_iType)
	{
	case BULLET_NORMAL:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 10.f, 10.f);
		m_tStat = STAT(2.f, 1.f, 18.f);
		break;

	case BULLET_KNIFE:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 10.f, 10.f);
		m_tStat = STAT(2.f, 1.f, 10.f);
		break;

	case BULLET_BOSS_11:								//보스1몬스터총알추가
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 10.f, 10.f);
		m_tStat = STAT(2.f, 1.f, 20.f);
		break;
	case BULLET_BOSS_12:								//보스1몬스터총알추가
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 10.f, 10.f);
		m_tStat = STAT(2.f, 1.f, 20.f);
		break;

	case BULLET_BOSS_13:								//보스1몬스터총알추가
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 10.f, 10.f);
		m_tStat = STAT(2.f, 1.f, 20.f);
		break;

	case BULLET_BOSS_2:							  	    //보스2몬스터총알추가
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 10.f, 10.f);
		m_tStat = STAT(2.f, 1.f, 20.f);
		break;
	}
}

void CBullet::Progress(float _fTime)
{
	switch (m_iType)
	{
	case BULLET_NORMAL:
		m_tInfo.fX += cos(m_fAngle * PI / 180) * m_tStat.fSpeed;
		m_tInfo.fY -= sin(m_fAngle * PI / 180) * m_tStat.fSpeed;
		break;

	case BULLET_KNIFE:
		m_tInfo.fX += cos(m_fAngle * PI / 180) * m_tStat.fSpeed;
		m_tInfo.fY -= sin(m_fAngle * PI / 180) * m_tStat.fSpeed;
		break;
	}
}

void CBullet::Render(HDC hdc)
{
	switch (m_iType)
	{
	case BULLET_NORMAL:
		Ellipse(hdc, 
			int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		break;

	case BULLET_KNIFE:
		if(m_fAngle <= 90.f)
		{
			MoveToEx(hdc, int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX), int(m_tInfo.fY - m_tInfo.fCY / 2.f), NULL);
			LineTo(hdc, int(m_tInfo.fX + m_fScrollX), int(m_tInfo.fY));
			LineTo(hdc, int(m_tInfo.fX + 5 + m_fScrollX), int(m_tInfo.fY + 5));
			LineTo(hdc, int(m_tInfo.fX + m_fScrollX), int(m_tInfo.fY + 10));
			LineTo(hdc, int(m_tInfo.fX -5 + m_fScrollX), int(m_tInfo.fY + 15));
		}
		else
		{
			MoveToEx(hdc, int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX), int(m_tInfo.fY - m_tInfo.fCY / 2.f), NULL);
			LineTo(hdc, int(m_tInfo.fX + m_fScrollX), int(m_tInfo.fY));
			LineTo(hdc, int(m_tInfo.fX - 5 + m_fScrollX), int(m_tInfo.fY + 5));
			LineTo(hdc, int(m_tInfo.fX + m_fScrollX), int(m_tInfo.fY + 10));
			LineTo(hdc, int(m_tInfo.fX +5 + m_fScrollX), int(m_tInfo.fY + 15));
		}

		break;
	}
}

void CBullet::Release(void)
{

}

