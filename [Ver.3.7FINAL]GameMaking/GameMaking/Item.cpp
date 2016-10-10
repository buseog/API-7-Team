#include "StdAfx.h"
#include "Item.h"

CItem::CItem(void)
{
}

CItem::CItem(int _iInput)
: m_iType(_iInput)
{
}

CItem::~CItem(void)
{
}

void CItem::Initialize(void)
{
	m_Timer.SetTimer();

	switch (m_iType)
	{
	case 1:
		m_tInfo = INFO(0.f, 0.f, 20.f, 20.f);
		m_tStat = STAT(1.f, 1.f, 1.f, 10.f);
		break;
	}
}

void CItem::Progress(float _Time)
{
	switch (m_iType)
	{
	case 1:
		NomalType();
		break;
	}
}

void CItem::Render(HDC hdc)
{
	Rectangle(hdc,
	int(m_tInfo.fX - m_tInfo.fCX / 2.f),
	int(m_tInfo.fY - m_tInfo.fCY / 2.f),
	int(m_tInfo.fX + m_tInfo.fCX / 2.f),
	int(m_tInfo.fY + m_tInfo.fCY / 2.f)
	);
}


void CItem::Release(void)
{
}

void CItem::NomalType(void)
{
	m_tInfo.fY += m_tStat.fSpeed;
}

