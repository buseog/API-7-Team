#include "StdAfx.h"
#include "MonBullet.h"

CMonBullet::CMonBullet(void)
{
}

CMonBullet::CMonBullet(int _iInput)
:m_iType(_iInput)
{
}

CMonBullet::~CMonBullet(void)
{
}


void CMonBullet::Initialize(void)
{
	srand(unsigned(time(NULL)));

	m_Timer.SetTimer();
	fDX = 0;
	fDY = 0;
	switch (m_iType)
	{
	case 1:
		m_tInfo = INFO(0.f, 0.f, 15.f, 25.f);
		m_tStat = STAT(1.f, 1.f, 2.f, 15.f);
		break;
	case 2:
		m_tInfo = INFO(0.f, 0.f, 15.f, 15.f);
		m_tStat = STAT(1.f, 1.f, 1.f, 10.f);
		break;
	case 3:
		m_tInfo = INFO(0.f, 0.f, 10.f, 50.f);
		m_tStat = STAT(1.f, 1.f, 3.f, 10.f);
		break;
	case 4:
		m_tInfo = INFO(0.f, 0.f, 10.f, 20.f);
		m_tStat = STAT(1.f, 1.f, 3.f, 10.f);
		break;
	}
}



void CMonBullet::Progress(float _Time)
{
	if (m_tInfo.fX > WINCX - 10 || m_tInfo.fX < 160 || m_tInfo.fY > WINCY - 10 || m_tInfo.fY < 10)
	{
		m_tStat.Destroy = TRUE;
	}
	switch (m_iType)
	{
	case 1:
		NomalType();
		break;
	case 2:
		TargetType();
		break;
	case 3:
		Razer();
		break;
	case 4:
		RandomType();
		break;
	}
}



void CMonBullet::Render(HDC hdc)
{
	Ellipse(hdc,
	int(m_tInfo.fX - m_tInfo.fCX / 2.f),
	int(m_tInfo.fY - m_tInfo.fCY / 2.f),
	int(m_tInfo.fX + m_tInfo.fCX / 2.f),
	int(m_tInfo.fY + m_tInfo.fCY / 2.f));
}



void CMonBullet::Release(void)
{
}

void CMonBullet::NomalType(void)
{
	m_tInfo.fY += m_tStat.fSpeed;
}

void CMonBullet::TargetType(void)
{
	m_tInfo.fX += (fDX * m_tStat.fSpeed);
	m_tInfo.fY += (fDY * m_tStat.fSpeed);
}

void CMonBullet::Razer(void)
{
	m_tInfo.fY += 30;
	m_tInfo.fCY += 60;
}

void CMonBullet::RandomType(void)
{
	if (fDX == 0)
	{
		fDX = rand() % 800 - m_tInfo.fX;
		fDY = (rand() % 600 + 200) - m_tInfo.fY;

		float fDistance = sqrt(fDX * fDX + fDY * fDY);
		fDX /= fDistance;
		fDY /= fDistance;
	}
	m_tInfo.fX += (fDX * m_tStat.fSpeed);
	m_tInfo.fY += (fDY * m_tStat.fSpeed);
}