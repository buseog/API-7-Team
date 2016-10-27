#include "StdAfx.h"
#include "Player.h"
#include "Bullet.h"
#include "ObjFactory.h"

CPlayer::CPlayer(void)
: m_bJump(false)
, m_fTime(0.f)
, m_iWeaponType(1)
{
}

CPlayer::CPlayer(int _iType)
{
	m_iType = _iType;
	m_iWeaponType = 1;
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_iRidecount = 0;
	m_fOffSetX = WINCX / 2.f;
	m_CTimer.SetTimer();		//타이머 세팅
	m_fDistance = 15.f;
	m_fMaxHp = 100.f;

	// 타입에 따른 플래그
	switch (m_iType)
	{
	case PLAYER_HUMAN:
		//구조체로 만들어준 INFO 값 입력.
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 40.f, 40.f);
		//구조체로 만들어둔 STAT 값 입력.
		// 체력 , 공격력(충돌처리하면서 미사일 터뜨리기위함), 스피드
		m_tStat = STAT(100.f, 1.f, 10.f);
		break;

	case PLAYER_TANK:
		break;
	}

	//hp바
	rc.left = 75;
	rc.top = 522;
	rc.right = 75 + (long)(m_tStat.fHp);
	rc.bottom = 535;
}

void CPlayer::Progress(float _fTime)
{
	rc.right = (long)(m_tStat.fHp) + rc.left;
	KeyInput(_fTime);			// 키입력함수
	Scroll();			// 화면 이동하는함수

	if(m_bJump)
	{
		m_fTime += 0.1f;

		m_tInfo.fY += -10.f + (5.f * m_fTime * m_fTime) / 2.f;
	}

	LineCollision();
}

void CPlayer::Render(HDC hdc)
{
	int iHp = (int)m_tStat.fHp;
	wsprintf(m_szHp, L"HP: %d", iHp);
	TextOut(hdc, 20, 520, m_szHp, lstrlen(m_szHp));
	HBRUSH m_Brush;
	HBRUSH m_oBrush;
	float fPercent = m_tStat.fHp / m_fMaxHp;
	if (fPercent >= 1.01f)
		fPercent = 1.f;
	if (fPercent <= 0.4)
	{
		m_Brush = CreateSolidBrush(RGB(255, 0, 0));
		m_oBrush = (HBRUSH)SelectObject(hdc, m_Brush);
	}
	else if (fPercent <= 0.6)
	{
		m_Brush = CreateSolidBrush(RGB(255, 255, 0));
		m_oBrush = (HBRUSH)SelectObject(hdc, m_Brush);
	}
	else
	{
		m_Brush = CreateSolidBrush(RGB(0, 255, 0));
		m_oBrush = (HBRUSH)SelectObject(hdc, m_Brush);
	}
	Rectangle(hdc, rc.left, rc.top, int(rc.left + (100 * fPercent)), rc.bottom);
	SelectObject(hdc, m_oBrush);
	DeleteObject(m_Brush);
	
	Rectangle(hdc, 200, 500, 400, 600);
	Rectangle(hdc, 230, 520, 290, 580);
	TextOut(hdc, 300, 530, TEXT("1번 권총"), 5);
	TextOut(hdc, 300, 560, TEXT("2번 칼"), 4);
	switch (m_iWeaponType)
	{
	case 1:
		MoveToEx(hdc, 240, 530, NULL);
		LineTo(hdc, 280, 550);
		MoveToEx(hdc, 280, 550, NULL);
		LineTo(hdc, 260, 570);
		break;
	case 2:
		MoveToEx(hdc, 260, 530, NULL);
		LineTo(hdc, 260, 570);
		MoveToEx(hdc, 250, 555, NULL);
		LineTo(hdc, 270, 555);
		break;
	}

	switch (m_iType)
	{
	case PLAYER_HUMAN:
		{
			if(m_iRidecount == 1)
			{
				m_tStat = STAT(100.f, 1.f, 8.f);
				m_iRidecount--;
			}
			
			switch (m_iWeaponType)
			{
			case 1:
				{
				//칼
				MoveToEx(hdc, (int)m_tInfo.fX - 10 + (int)m_fScrollX, (int)m_tInfo.fY - 10, NULL);
				LineTo(hdc, (int)m_tInfo.fX + 10 + (int)m_fScrollX, (int)m_tInfo.fY + 10);
				//왼다리
				MoveToEx(hdc, (int)m_tInfo.fX + (int)m_fScrollX, (int)m_tInfo.fY + 10, NULL);
				LineTo(hdc, (int)m_tInfo.fX - 15 + (int)m_fScrollX, (int)m_tInfo.fY + 25);
				//오른다리
				MoveToEx(hdc, (int)m_tInfo.fX + (int)m_fScrollX, (int)m_tInfo.fY + 10, NULL);
				LineTo(hdc, (int)m_tInfo.fX + 15 + (int)m_fScrollX, (int)m_tInfo.fY + 25);
				//몸통
				MoveToEx(hdc, (int)m_tInfo.fX + (int)m_fScrollX, (int)m_tInfo.fY + 10, NULL);
				LineTo(hdc, (int)m_tInfo.fX + (int)m_fScrollX, (int)m_tInfo.fY - 10);
				//머리
				Ellipse(hdc, (int)m_tInfo.fX - 5 + (int)m_fScrollX, (int)m_tInfo.fY - 13, (int)m_tInfo.fX + 5 + (int)m_fScrollX, (int)m_tInfo.fY - 3);

				//팔
				MoveToEx(hdc, (int)m_tInfo.fX + (int)m_fScrollX, (int)m_tInfo.fY, NULL);

				fX = m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * m_fDistance;
				fY = m_tInfo.fY - sinf(m_fAngle * PI / 180.f) * m_fDistance;

				LineTo(hdc, (int)fX + (int)m_fScrollX, (int)fY);
				//총
				MoveToEx(hdc, (int)fX + (int)m_fScrollX, (int)fY + 5, NULL);
				LineTo(hdc, (int)fX + (int)m_fScrollX, (int)fY - 5);
				
				float fGun = m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * (m_fDistance + 20);
				LineTo(hdc, (int)fGun + (int)m_fScrollX, (int)fY - 5);
				}
				break;

			case 2:
				{
				MoveToEx(hdc, (int)m_tInfo.fX + (int)m_fScrollX, (int)m_tInfo.fY + 10, NULL);
				LineTo(hdc, (int)m_tInfo.fX - 15 + (int)m_fScrollX, (int)m_tInfo.fY + 25);
				MoveToEx(hdc, (int)m_tInfo.fX + (int)m_fScrollX, (int)m_tInfo.fY + 10, NULL);
				LineTo(hdc, (int)m_tInfo.fX + 15 + (int)m_fScrollX, (int)m_tInfo.fY + 25);
				MoveToEx(hdc, (int)m_tInfo.fX + (int)m_fScrollX, (int)m_tInfo.fY + 10, NULL);
				LineTo(hdc, (int)m_tInfo.fX + (int)m_fScrollX, (int)m_tInfo.fY - 10);
				Ellipse(hdc, (int)m_tInfo.fX - 5 + (int)m_fScrollX, (int)m_tInfo.fY - 13, (int)m_tInfo.fX + 5 + (int)m_fScrollX, (int)m_tInfo.fY - 3);

				//팔
				MoveToEx(hdc, (int)m_tInfo.fX + (int)m_fScrollX, (int)m_tInfo.fY, NULL);

				fX = m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * m_fDistance;
				fY = m_tInfo.fY - sinf(m_fAngle * PI / 180.f) * m_fDistance;

				LineTo(hdc, (int)fX + (int)m_fScrollX, (int)fY);
				//칼
				MoveToEx(hdc, (int)fX + (int)m_fScrollX, (int)fY + 5, NULL);
				LineTo(hdc, (int)fX + (int)m_fScrollX, (int)fY - 20);
				MoveToEx(hdc, (int)fX - 5 + (int)m_fScrollX, (int)fY - 3, NULL);
				LineTo(hdc, (int)fX + 5 + (int)m_fScrollX, (int)fY - 3);
				//총
				MoveToEx(hdc, (int)m_tInfo.fX + (int)m_fScrollX, (int)m_tInfo.fY, NULL);
				LineTo(hdc, (int)m_tInfo.fX + 10 + (int)m_fScrollX, (int)m_tInfo.fY - 5);

				MoveToEx(hdc, (int)m_tInfo.fX + (int)m_fScrollX, (int)m_tInfo.fY, NULL);
				LineTo(hdc, (int)m_tInfo.fX + 2 + (int)m_fScrollX, (int)m_tInfo.fY + 5);
				}
				break;
			}

		}
		break;

	case PLAYER_TANK:

		if(m_iRidecount == 0)
		{
			m_tStat = STAT(250.f, 5.f, 8.f);
			m_iRidecount++;
			m_iWeaponType = 1;
		}
	
		Rectangle(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		Ellipse(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		MoveToEx(hdc, (int)m_tInfo.fX + (int)m_fScrollX, (int)m_tInfo.fY, NULL);

		fX = m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * m_fDistance *2;
		fY = m_tInfo.fY - sinf(m_fAngle * PI / 180.f) * m_fDistance *2;

		LineTo(hdc, (int)fX + (int)m_fScrollX, (int)fY);
		break;
	}
}

void CPlayer::Release(void)	
{

}

void CPlayer::Scroll(void)
{
	if(m_tInfo.fX > m_fOffSetX + 100 && m_tInfo.fX <= 3700)
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

void CPlayer::KeyInput(float _fTime)
{
	if(GetAsyncKeyState(VK_SPACE))
	{
		m_tStat.fHp = 10000;
	}
	if(GetAsyncKeyState(VK_LEFT))
	{
		if (m_tInfo.fX >= 10)
		{
			m_tInfo.fX -= m_tStat.fSpeed;
			m_fAngle    = 180.f;
		}
	}

	if(GetAsyncKeyState(VK_SHIFT))
	{
		m_iType = PLAYER_HUMAN;
	}

	if(GetAsyncKeyState(VK_RIGHT))
	{
		if (m_tInfo.fX <= 3950)
		{
			m_tInfo.fX += m_tStat.fSpeed;
			m_fAngle    = 0.f;
		}
	}

	if(GetAsyncKeyState(VK_UP))
	{
		if (m_fAngle <= 90)
		{
			m_fAngle += 5.f;
		}
		else
		{
			m_fAngle -= 5.f;
		}

	}

	if(GetAsyncKeyState(VK_DOWN))
	{
		m_fAngle = 270.f;
	}

	if(GetAsyncKeyState('1'))   //총 구별 (기본총)
		m_iWeaponType = 1;

	if(GetAsyncKeyState('2'))   //총 구별 (나이프)
	{
		if(m_iType == PLAYER_HUMAN)
			m_iWeaponType = 2;
		else
			m_iWeaponType = 1;
	}

	if(GetAsyncKeyState('X'))
	{
		if(m_bJump)
		{
			return;
		}
		m_fTime = 0.f;
		m_bJump = true;
	}

	if(GetAsyncKeyState('Z'))
	{
		if ((m_CTimer.m_fRemainTime[0] -= _fTime) <= 0)
		{
			switch(m_iWeaponType) // 총스왑
			{
			case 1:
				m_pBulletList->push_back(CreateBullet(m_fAngle, BULLET_NORMAL));
				break;

			case 2:
				if (m_fAngle == 0.f || m_fAngle == 180.f)
				m_pBulletList->push_back(CreateBullet(m_fAngle, BULLET_KNIFE));
				break;

			default:
				m_pBulletList->push_back(CreateBullet(m_fAngle, BULLET_NORMAL));
				break;
			}
			m_CTimer.m_fRemainTime[0] = 150;
		}
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

	float fY = fGradient * (m_tInfo.fX - pLine->tLPoint.fX) + pLine->tLPoint.fY - 10;

	if (m_tInfo.fY >= fY)
	{
		m_fTime = 0.f;
		m_bJump = false;
		m_tInfo.fY = fY - 15;
	}

	else if (m_tInfo.fY < fY - 20 && m_bJump == false)
		m_tInfo.fY += m_tStat.fSpeed;
}

void CPlayer::SetLine(list<LINE*>* pLine)
{
	m_pLine = pLine;
}

void CPlayer::SetBulletList(list<CObj*>* pBulletList)
{
	m_pBulletList = pBulletList;
}

CObj* CPlayer::CreateBullet(float _fAngle, int _iType)
{
	fX = m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * m_fDistance;
	fY = m_tInfo.fY - sinf(m_fAngle * PI / 180.f) * m_fDistance;

	CObj*		pBullet = CObjFactory<CBullet>::CreateObj(fX, fY, _iType);
	pBullet->SetAngle(_fAngle);

	return pBullet;
}

void CPlayer::SetJump(bool YN)
{
	m_bJump = YN;
}

void	CPlayer::SetScrollX(void)
{
	m_fScrollX = 0.f;
}

void	CPlayer::SetOffset(void)
{
	m_fOffSetX = WINCX / 2.f;
}

void	CPlayer::SetStageUp(void)
{
	SetOffset();
	SetPos(100.f, 400.f);
	SetScrollX();
}