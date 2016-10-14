#include "StdAfx.h"
#include "Box.h"

CBox::CBox(void)
{
}

CBox::CBox(int _iType)
{
	m_iType = _iType;
}

CBox::~CBox(void)
{
}

void CBox::Initialize(void)
{
	switch (m_iType)
	{
	case BOX_NORMAL:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 60.f, 60.f);
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	}
}

void CBox::Progress(void)
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
			int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		break;
	}
}

void CBox::Release(void)
{
}