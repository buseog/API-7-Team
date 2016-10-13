#include "StdAfx.h"
#include "Monster.h"

CMonster::CMonster(void)
{
}

CMonster::CMonster(int _iType)
{
	m_iType = _iType;
}

CMonster::~CMonster(void)
{
}

void CMonster::Initialize(void)
{
	switch (m_iType)
	{
	case MONSTER_1:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	case MONSTER_2:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	}
}

void CMonster::Progress(void)
{
	switch (m_iType)
	{
	case MONSTER_1:
			break;
	}
}

void CMonster::Render(HDC hdc)
{
	switch (m_iType)
	{
	case MONSTER_1:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	case MONSTER_2:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	}
}

void CMonster::Release(void)
{
}