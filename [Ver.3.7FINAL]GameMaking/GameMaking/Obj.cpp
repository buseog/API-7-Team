#include "StdAfx.h"
#include "Obj.h"

CObj::CObj(void)
{
}

CObj::CObj(int _iInput)
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
void CObj::SetXY(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}

void CObj::SetDestroy(void)
{
	m_tStat.Destroy = TRUE;
}

void CObj::SetDamage(float _fAttack)
{
	m_tStat.fHp -= _fAttack;
}

void CObj::StatRender(void)
{
	m_hdc = GetDC(g_hWnd);
	HBRUSH m_Brush;
    HBRUSH m_oBrush;
	float fPercent = m_tStat.fHp / m_tStat.fFullHp;
	if (fPercent <= 0.4)
	{
		m_Brush = CreateSolidBrush(RGB(255,0,0));
		m_oBrush = (HBRUSH)SelectObject(m_hdc,m_Brush);
	}
	else if (fPercent <= 0.6)
	{
		m_Brush = CreateSolidBrush(RGB(255,255,0));
		m_oBrush = (HBRUSH)SelectObject(m_hdc,m_Brush);
	}
	else
	{
		m_Brush = CreateSolidBrush(RGB(0,255,0));
		m_oBrush = (HBRUSH)SelectObject(m_hdc,m_Brush);
	}
	RECT rc = {
		int(m_tInfo.fX - 50),
		int(m_tInfo.fY + 30),
		int((m_tInfo.fX - 50) + (100 * fPercent)),
		int(m_tInfo.fY + 40)};

	Rectangle(m_hdc, rc.left, rc.top, rc.right, rc.bottom);
	SelectObject(m_hdc,m_oBrush);
    DeleteObject(m_Brush);
}


void CObj::SetDXY(float _fX, float _fY)
{
	fDX += _fX;
	fDY += _fY;
}

float CObj::GetfDX(void)
{
	return fDX;
}