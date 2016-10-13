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
	switch (m_iType)
	{
	case BULLET_NORMAL:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 10.f, 10.f);
		m_tStat = STAT(2.f, 1.f, 5.f);
		break;
	}
}

void CBullet::Progress(void)
{
	switch (m_iType)
	{
	case BULLET_NORMAL:
		m_tInfo.fX += 5.f;
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
	}
}

void CBullet::Release(void)
{

}