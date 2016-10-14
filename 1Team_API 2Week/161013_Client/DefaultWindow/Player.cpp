#include "StdAfx.h"
#include "Player.h"
#include "Bullet.h"
#include "ObjFactory.h"

CPlayer::CPlayer(void)
: m_bJump(false)
, m_fTime(0.f)
, m_fAngle(0.f)
{
}

CPlayer::CPlayer(int _iType)
{
	m_iType = _iType;
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_fOffSetX = WINCX / 2.f;
	// 타입에 따른 플래그
	switch (m_iType)
	{
	case PLAYER_HUMAN:
		//구조체로 만들어준 INFO 값 입력.
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 40.f, 40.f);
		//구조체로 만들어둔 STAT 값 입력.
		// 체력 , 공격력(충돌처리하면서 미사일 터뜨리기위함), 스피드
		m_tStat = STAT(10.f, 1.f, 7.f);
		break;
	case PLAYER_TANK:
		break;
	}
}

void CPlayer::Progress(void)
{
	KeyInput();	
	Scroll();

	if(m_bJump)
	{
		m_fTime += 0.1f;

		m_tInfo.fY += -10.f + (6.f * m_fTime * m_fTime) / 2.f;
	}

	LineCollision();
}

void CPlayer::Render(HDC hdc)
{
	// 렌더링도 플래그값으로 바꿔줌.
	switch (m_iType)
	{
	case PLAYER_HUMAN:
		Rectangle(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		break;
	case PLAYER_TANK:
		break;
	}
}

void CPlayer::Release(void)
{
	
}

void CPlayer::Scroll(void)
{
	if(m_tInfo.fX > m_fOffSetX + 100)
	{
		m_fScrollX -= m_tStat.fSpeed;
		m_fOffSetX += m_tStat.fSpeed;
	}

	if (m_tInfo.fX < m_fOffSetX - 100 && m_tInfo.fX > 300)
	{
		m_fScrollX += m_tStat.fSpeed;
		m_fOffSetX -= m_tStat.fSpeed;
	}
}

void CPlayer::KeyInput(void)
{
	if(GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_tStat.fSpeed;
	}

	if(GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_tStat.fSpeed;
	}

	if(GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_tStat.fSpeed;

	if(GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_tStat.fSpeed;

	if(GetAsyncKeyState('X'))
	{
		if(m_bJump)
			return;
		m_fTime = 0.f;
		m_bJump = true;
	}

	if(GetAsyncKeyState('Z') & 0x8000)
	{
		m_pBulletList->push_back(CObjFactory<CBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, BULLET_NORMAL));
	}
}

void CPlayer::LineCollision(void)
{
	LINE*		pLine = NULL;

	for(list<LINE*>::iterator	iter = m_pLine->begin();
		iter != m_pLine->end(); ++iter)
	{
		if((*iter)->tLPoint.fX < m_tInfo.fX && m_tInfo.fX < (*iter)->tRPoint.fX)
		{
			pLine = (*iter);
			break;
		}
	}

	if(pLine == NULL)
		return; 

	float fWidth  = pLine->tRPoint.fX - pLine->tLPoint.fX;
	float fHeight = pLine->tRPoint.fY - pLine->tLPoint.fY;

	float fGradient = fHeight / fWidth;

	float fY = fGradient * (m_tInfo.fX - pLine->tLPoint.fX) + pLine->tLPoint.fY;

	if (m_tInfo.fY > fY)
	{
		m_fTime = 0.f;
		m_bJump = false;
		m_tInfo.fY = fY;
	}
	else if (m_tInfo.fY < fY && m_bJump == false)
		m_tInfo.fY += m_tStat.fSpeed;


}
void CPlayer::SetJumpOff(void)
{
	m_bJump = false;
}
void CPlayer::SetLine(list<LINE*>* pLine)
{
	m_pLine = pLine;
}

void CPlayer::SetBulletList(list<CObj*>* pBulletList)
{
	m_pBulletList = pBulletList;
}