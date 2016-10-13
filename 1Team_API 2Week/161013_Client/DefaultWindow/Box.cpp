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
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
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
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	}
}

void CBox::Release(void)
{
}