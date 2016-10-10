#include "StdAfx.h"
#include "Bullet.h"

CBullet::CBullet(void)
{
}

CBullet::CBullet(int _iInput)
: m_iType(_iInput)
{
}

CBullet::~CBullet(void)
{
	Release();
}

void CBullet::Initialize(void)	
{
	m_Timer.SetTimer();
	m_iStan = 0;
	fDX = 0;
	fDY = 0;
	switch (m_iType)
	{
	case 1:
		m_tInfo = INFO(0.f, 0.f, 20.f, 20.f);
		m_tStat = STAT(1.f, 1.f, 2.f, 10.f);
		m_tStat.iKey = 1;
		break;
	case 2:
		m_tInfo = INFO(0.f, 0.f, 10.f, 10.f);
		m_tStat = STAT(1.f, 1.f, 1.f, 12.f);
		m_tStat.iKey = 2;
		break;
	case 3:
		m_tInfo = INFO(0.f, 0.f, 5.f, 5.f);
		m_tStat = STAT(1.f, 1.f, 0.5f, 7.f);
		m_tStat.iKey = 3;
		break;
	case 4:
		m_tInfo = INFO(0.f, 0.f, 10.f, 10.f);
		m_tStat = STAT(1.f, 1.f, 0.8f, 15.f);
		m_tStat.iKey = 4;
		break;
	case 5:
		m_tInfo = INFO(0.f, 0.f, 300.f, 300.f);
		m_tStat = STAT(60.f, 60.f, 0.5f, 15.f);
		m_tStat.iKey = 5;
		break;
	}

}

void CBullet::Progress(float _Time)
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
		if((m_Timer.RemainTime[0] -= _Time) <= 0)
		{
			TargetType(_Time);
			m_Timer.RemainTime[0] = 30;
		}
		break;
	case 3:
		ChargeType(_Time);
		break;
	case 4:
		BuckType();
		break;
	case 5:
		UltiType(_Time);
		break;
	}
}

void CBullet::Render(HDC hdc)
{
	Ellipse(hdc,
		int(m_tInfo.fX - m_tInfo.fCX / 2.f -3),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f -3),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f +3),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f +3));

	if (m_iStan < 2)
	{
		MoveToEx(hdc, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY/2, NULL);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX/2, m_tInfo.fY - m_tInfo.fCY/4);
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCY/2, m_tInfo.fY - m_tInfo.fCY/4);
		LineTo(hdc, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY/2);
		
		MoveToEx(hdc, m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY/2, NULL);
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX/2, m_tInfo.fY + m_tInfo.fCY/4);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCY/2, m_tInfo.fY + m_tInfo.fCY/4);
		LineTo(hdc, m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY/2);
		++m_iStan;
	}
	else
	{
		MoveToEx(hdc, m_tInfo.fX + m_tInfo.fCX/2, m_tInfo.fY, NULL);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX/4, m_tInfo.fY - m_tInfo.fCY/2);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCY/4, m_tInfo.fY + m_tInfo.fCY/2);
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX/2, m_tInfo.fY);

		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX/2, m_tInfo.fY, NULL);
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX/4, m_tInfo.fY + m_tInfo.fCY/2);
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCY/4, m_tInfo.fY - m_tInfo.fCY/2);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX/2, m_tInfo.fY);
		++m_iStan;

		if (m_iStan == 4)
		{
			m_iStan = 0;
		}
	}
}

void CBullet::Release(void)
{
}

void CBullet::NomalType(void)
{
	m_tInfo.fY -= m_tStat.fSpeed;
}

void CBullet::TargetType(float _Time)
{
	m_tInfo.fX += (fDX * m_tStat.fSpeed);
	m_tInfo.fY += (fDY * m_tStat.fSpeed);
	m_Timer.RemainTime[0] = 60;
}

void CBullet::ChargeType(float _Time)
{
	if ((m_Timer.RemainTime[5] -= _Time) <= 0)
	{
		SetDestroy();	
	}
	else
	{
		m_tInfo.fCX += 0.4f;
		m_tInfo.fCY += 0.4f;
		m_tStat.fAttack += 0.05;
	}
}

void CBullet::BuckType(void)
{
	if (fDX == 0)
	{
		fDX = (rand() % 600 + 200) - m_tInfo.fX;
		fDY = (m_tInfo.fY - 150) - m_tInfo.fY;

		float fDistance = sqrt(fDX * fDX + fDY * fDY);
		fDX /= fDistance;
		fDY /= fDistance;
	}
	m_tInfo.fX += (fDX * m_tStat.fSpeed);
	m_tInfo.fY += (fDY * m_tStat.fSpeed);
}

void CBullet::UltiType(float _Time)
{
	if ((m_Timer.RemainTime[7] -= _Time) <= 0)
	{
		SetDestroy();	
	}

	fDX = 400 - m_tInfo.fX;
	fDY = 300 - m_tInfo.fY;

	float fDistance = sqrt(fDX * fDX + fDY * fDY);
	fDX /= fDistance;
	fDY /= fDistance;

	m_tInfo.fX += (fDX * m_tStat.fSpeed);
	m_tInfo.fY += (fDY * m_tStat.fSpeed);
}