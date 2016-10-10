#include "StdAfx.h"
#include "Obj.h"

CObj::CObj(void)
{
}

CObj::~CObj(void)
{
}

INFO CObj::GetInfo(void)
{
	return m_tInfo;
}

void CObj::SetPos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}

/*RECT CObj::GetRect(void)
{
	//디자인 확정 후 코드 삽입
}*/