#include "StdAfx.h"
#include "Player.h"

CPlayer::CPlayer(void)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::KeyInput(void)
{
	if(GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if(GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if(GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if(GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;
}

void CPlayer::Initialize(void)
{
	m_tInfo  = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);
	m_fSpeed = 10.f;
}

void CPlayer::Progress(void)
{
	KeyInput();	
}

void CPlayer::Render(HDC hdc)
{
	Rectangle(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f));
}

void CPlayer::Release(void)
{
	
}
