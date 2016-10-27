#include "StdAfx.h"
#include "Obj.h"

CObj::CObj(void)
: m_fSpeed(0.f)
, m_fDistance(0.f)
, m_fAngle(0.f)
{
}

CObj::~CObj(void)
{
}

INFO CObj::GetInfo(void)
{
	return m_tInfo;
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
