#include "StdAfx.h"
#include "Item.h"

CItem::CItem(void)
{
}

CItem::CItem(int _iType)
{
	m_iType = _iType;
}

CItem::~CItem(void)
{
}

void CItem::Initialize(void)
{
	switch (m_iType)
	{
	case ITEM_ATTACK:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	case ITEM_RECOVERY:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 0.f);
		break;
	}
}

void CItem::Progress(void)
{
	switch (m_iType)
	{
	case ITEM_ATTACK:
			break;
	}
}

void CItem::Render(HDC hdc)
{
	switch (m_iType)
	{
	case ITEM_ATTACK:
		Rectangle(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		break;
	case ITEM_RECOVERY:
		Rectangle(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		break;
	}
}

void CItem::Release(void)
{
}