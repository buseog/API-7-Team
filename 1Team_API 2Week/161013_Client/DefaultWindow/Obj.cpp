#include "StdAfx.h"
#include "Obj.h"

float CObj::m_fScrollX = 0.f;

CObj::CObj(void)
{
}
CObj::CObj(int _iType)
{
}
CObj::~CObj(void)
{
}

INFO CObj::GetInfo(void)
{
	return m_tInfo;
}
STAT CObj::GetStat(void)
{
	return m_tStat;
}
RECT CObj::GetRect(void)
{
	RECT		rc = {
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f)

	};

	return rc;
}

void CObj::SetPos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}

void CObj::SetDamage(float _fAttack)
{
	m_tStat.fHp -= _fAttack;
}

float CObj::GetScrollX(void)
{
	return m_fScrollX;
}
