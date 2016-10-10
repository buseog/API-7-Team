#include "StdAfx.h"
#include "Player.h"
#include "Bullet.h"
#include "AbstractFactory.h"

CPlayer::CPlayer(void)
{
}

CPlayer::CPlayer(int _iInput)
: m_iType(_iInput)
{
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::SetBulletList(list<CObj*>* pBullet)
{
	m_pBullet = pBullet;
}

void CPlayer::SetItemList(std::list<CObj*> *pItem)
{
	m_pItem = pItem;
}

void CPlayer::KeyInput(void)
{
	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_tStat.fSpeed;

	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_tStat.fSpeed;

	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_tStat.fSpeed;

	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_tStat.fSpeed;

	if (GetAsyncKeyState(VK_F1))
		m_iType = 1;

	if (GetAsyncKeyState(VK_F2))
		m_iType = 2;

	if (GetAsyncKeyState(VK_F3))
		m_iType = 3;

	if (GetAsyncKeyState(VK_F4))
		m_iType = 4;

	if (GetAsyncKeyState(VK_F12))
	{
		m_tStat.fHp = 500;
		m_tStat.fFullHp = 500;
	}
	
}

void CPlayer::Initialize(void)
{
	m_Timer.SetTimer();

	iStan = 0;
	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 40.f, 40.f);
	m_tStat = STAT(10.f, 10.f, 1.f, 10.f);
	m_iType = 1;
}

void CPlayer::Progress(float _Time)
{
	KeyInput();

	if ((m_Timer.RemainTime[9] -= _Time) <= 0)
	{
		if (GetAsyncKeyState(VK_CONTROL))
		{
			m_pBullet->push_back(CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, 5));
			m_Timer.RemainTime[9] = 12000;
		}
	}

	if ((m_Timer.RemainTime[0] -= _Time) <= 0)
	{
		if(GetAsyncKeyState(VK_SPACE))
		{
			if (m_iType < 4)
			{
				m_pBullet->push_back(CAbstractFactory<CBullet>::
				CreateObj(m_tInfo.fX, m_tInfo.fY, m_iType));
			}
			else if (m_iType == 4)
			{
				m_pBullet->push_back(CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, m_iType));
				m_pBullet->push_back(CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, m_iType));
				m_pBullet->push_back(CAbstractFactory<CBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, m_iType));
			}
		}
		m_Timer.RemainTime[0] = 200;
	}

	if (m_tInfo.fX <= 160)
		m_tInfo.fX += 20;
	if (m_tInfo.fX >= 790)
		m_tInfo.fX -= 20;
	if (m_tInfo.fY <= 10)
		m_tInfo.fY += 20;
	if (m_tInfo.fY >= 590)
		m_tInfo.fY -= 20;
}

void CPlayer::Render(HDC hdc)
{
	Ellipse(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f - 5),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f - 5),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f + 5),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f + 5));

		if (iStan < 3)
		{
			MoveToEx(hdc, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY/2, NULL);
			LineTo(hdc, m_tInfo.fX - m_tInfo.fCX/2, m_tInfo.fY - m_tInfo.fCY/4);
			LineTo(hdc, m_tInfo.fX + m_tInfo.fCY/2, m_tInfo.fY - m_tInfo.fCY/4);
			LineTo(hdc, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY/2);
			
			MoveToEx(hdc, m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY/2, NULL);
			LineTo(hdc, m_tInfo.fX + m_tInfo.fCX/2, m_tInfo.fY + m_tInfo.fCY/4);
			LineTo(hdc, m_tInfo.fX - m_tInfo.fCY/2, m_tInfo.fY + m_tInfo.fCY/4);
			LineTo(hdc, m_tInfo.fX, m_tInfo.fY - m_tInfo.fCY/2);
			++iStan;
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
			++iStan;

			if (iStan == 6)
			{
				iStan = 0;
			}
		}
}

void CPlayer::Release(void)
{
	
}

int	CPlayer::GetBulletType(void)
{
	return m_iType;
}