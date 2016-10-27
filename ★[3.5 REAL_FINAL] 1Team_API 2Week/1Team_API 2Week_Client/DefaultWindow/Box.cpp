#include "StdAfx.h"
#include "Box.h"

CBox::CBox(void)
{
	m_iType = BOX_NORMAL;
}

CBox::CBox(int _iType)
{
}

CBox::~CBox(void)
{
}

void CBox::Initialize(void)
{
	m_CTimer.SetTimer();

	switch (m_iType)
	{
	case BOX_NORMAL:
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	}
}

void CBox::Progress(float _fTime)
{
	switch (m_iType)
	{
	case BOX_NORMAL:
			break;
	}
}

void CBox::Render(HDC hdc)
{
	switch (m_iType)
	{
	case BOX_NORMAL:
		Rectangle(hdc,
			int(m_tInfo.fX + m_fScrollX),
			int(m_tInfo.fY),
			int(m_tInfo.fCX + m_fScrollX),
			int(m_tInfo.fCY));
		break;
	}
}

void CBox::Release(void)
{
}

void CBox::SetPoint(float _fleft, float _ftop, float _fright, float _fbottom)
{
	m_tInfo.fX = _fleft;
	m_tInfo.fY = _ftop;
	m_tInfo.fCX = _fright;
	m_tInfo.fCY = _fbottom;
}


RECT CBox::GetBox(void)
{
	RECT rc = {
		int(m_tInfo.fX),
		int(m_tInfo.fY),
		int(m_tInfo.fCX),
		int(m_tInfo.fCY)
	};

	return rc;
}
