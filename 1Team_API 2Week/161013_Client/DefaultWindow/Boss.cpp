#include "StdAfx.h"
#include "Boss.h"

CBoss::CBoss(void)
{
}

CBoss::CBoss(int _iType)
{
	m_iType = _iType;
}

CBoss::~CBoss(void)
{
}

void CBoss::Initialize(void)
{
	switch (m_iType)
	{
	case BOSS_1:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	case BOSS_2:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	}
}

void CBoss::Progress(void)
{
	switch (m_iType)
	{
	case BOSS_1:
			break;
	}
}

void CBoss::Render(HDC hdc)
{
	switch (m_iType)
	{
	case BOSS_1:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	case BOSS_2:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	}
}

void CBoss::Release(void)
{
}