#include "StdAfx.h"
#include "Monster.h"
#include "ObjFactory.h"
#include "MonsterBullet.h"

CMonster::CMonster(void)
{
}

CMonster::CMonster(int _iType)
{
	m_iType = _iType;
	m_pPlayer = NULL;
}

CMonster::~CMonster(void)
{
}

void CMonster::Initialize(void)
{
	m_CTimer.SetTimer();

	switch (m_iType)
	{
	case MONSTER_1:   //일반1 총알쏘는몬스터
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 60.f, 60.f);
		m_tStat = STAT(1.f, 1.f, 5.f);
		break;
	case MONSTER_2:   //일반2 자폭 몬스터
		m_tInfo = INFO(200.f, 200.f, 30.f, 30.f);
		m_tStat = STAT(1.f, 1.f, 5.f);
		break;
	case MONSTER_3:   //일반3 함정 몬스터
		m_tInfo = INFO(200.f, 200.f, 70.f, 30.f);
		m_tStat = STAT(100.f, 100.f, 5.f);
		break;
	}
}

void CMonster::Progress(float _fTime)
{
	switch (m_iType)
	{
	case MONSTER_1:
		if ((m_CTimer.m_fRemainTime[0] -= _fTime) <= 0)
		{
			float	fWidth = m_pPlayer->GetInfo().fX - m_tInfo.fX;    //쌤코드 몬스터가 플레이어따라가는거
			float	fHeight = m_pPlayer->GetInfo().fY - m_tInfo.fY;

			float   fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

			float m_PlayerfAngle = acosf(fWidth / fDistance) * 180.f / PI;		// Radian to degree

			if (m_pPlayer->GetInfo().fY >= m_tInfo.fY)
			{
				m_PlayerfAngle = 360.f - m_PlayerfAngle;
			}
			m_pMBulletList->push_back(CObjFactory<CMonsterBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY, BULLET_NORMAL, m_PlayerfAngle));
			m_CTimer.m_fRemainTime[0] = 400;
		}
		break;

	case MONSTER_2:
		if(m_tInfo.fX - m_pPlayer->GetInfo().fX <= 400)
		{
			float	fWidth = m_pPlayer->GetInfo().fX - m_tInfo.fX;    //쌤코드 몬스터가 플레이어따라가는거
			float	fHeight = m_pPlayer->GetInfo().fY - m_tInfo.fY;

			float   fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

			m_fAngle = acosf(fWidth / fDistance) * 180.f / PI;		// Radian to degree

			if(m_pPlayer->GetInfo().fY > m_tInfo.fY)
			{
				m_fAngle = 360.f - m_fAngle;
			}

			m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_tStat.fSpeed;	
			m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_tStat.fSpeed;
		}
		break;
	case MONSTER_3:
		break;
	}
}

void CMonster::Render(HDC hdc)
{
	switch (m_iType)
	{
	case MONSTER_1:
		Rectangle(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		if (true)
		{
			MoveToEx(hdc, (int)(m_tInfo.fX + m_fScrollX), (int)m_tInfo.fY, NULL);
			float	fWidth = m_pPlayer->GetInfo().fX - m_tInfo.fX;    //쌤코드 몬스터가 플레이어따라가는거
			float	fHeight = m_pPlayer->GetInfo().fY - m_tInfo.fY;
			float   fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);
			m_fAngle = acosf(fWidth / fDistance) * 180.f / PI;
			if (m_pPlayer->GetInfo().fY > m_tInfo.fY)
			{
				m_fAngle = 360.f - m_fAngle;
			}
			LineTo(hdc, int((m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * 25.f + m_fScrollX)), int(m_tInfo.fY - sinf(m_fAngle * PI / 180.f) * 25.f));
				Ellipse(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 4.f + m_fScrollX),
			int(m_tInfo.fY - m_tInfo.fCY / 4.f),
			int(m_tInfo.fX + m_tInfo.fCX / 4.f + m_fScrollX),
			int(m_tInfo.fY + m_tInfo.fCY / 4.f));
		}
		break;
	case MONSTER_2:
		MoveToEx(hdc, int(m_tInfo.fX - 6 + m_fScrollX), int(m_tInfo.fY - 10), NULL);
		LineTo(hdc, int(m_tInfo.fX - 6 + m_fScrollX), int(m_tInfo.fY - 20));
		LineTo(hdc, int(m_tInfo.fX + 6 + m_fScrollX), int(m_tInfo.fY - 20));
		LineTo(hdc, int(m_tInfo.fX + 6 + m_fScrollX), int(m_tInfo.fY - 10));
		MoveToEx(hdc, int(m_tInfo.fX + m_fScrollX), int(m_tInfo.fY - 20), NULL);
		LineTo(hdc, int(m_tInfo.fX + m_fScrollX), int(m_tInfo.fY - 27));
		Ellipse(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY - m_tInfo.fCY / 2.f),
			int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
			int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		MoveToEx(hdc, int(m_tInfo.fX - 10 + m_fScrollX), int(m_tInfo.fY - 5), NULL);
		LineTo(hdc, int(m_tInfo.fX + 10 + m_fScrollX), int(m_tInfo.fY + 5));
		MoveToEx(hdc, int(m_tInfo.fX + 10 + m_fScrollX), int(m_tInfo.fY - 5), NULL);
		LineTo(hdc, int(m_tInfo.fX - 10 + m_fScrollX), int(m_tInfo.fY + 5));
		break;
	case MONSTER_3:
		MoveToEx(hdc, int(m_tInfo.fX - 70 / 2 + m_fScrollX), int(m_tInfo.fY + 30 / 2), NULL);
		LineTo(hdc, int(m_tInfo.fX - 70 / 2 + m_fScrollX), int(m_tInfo.fY + 30 / 2 - 30));
		LineTo(hdc, int(m_tInfo.fX - 70 / 2 + 7 + m_fScrollX), int(m_tInfo.fY + 30 / 2 - 30 + 15));
		LineTo(hdc, int(m_tInfo.fX - 70 / 2 + 14 + m_fScrollX), int(m_tInfo.fY + 30 / 2 - 30));
		LineTo(hdc, int(m_tInfo.fX - 70 / 2 + 21 + m_fScrollX), int(m_tInfo.fY + 30 / 2 - 30 + 15));
		LineTo(hdc, int(m_tInfo.fX - 70 / 2 + 28 + m_fScrollX), int(m_tInfo.fY + 30 / 2 - 30));
		LineTo(hdc, int(m_tInfo.fX - 70 / 2 + 35 + m_fScrollX), int(m_tInfo.fY + 30 / 2 - 30 + 15));
		LineTo(hdc, int(m_tInfo.fX - 70 / 2 + 42 + m_fScrollX), int(m_tInfo.fY + 30 / 2 - 30));
		LineTo(hdc, int(m_tInfo.fX - 70 / 2 + 49 + m_fScrollX), int(m_tInfo.fY + 30 / 2 - 30 + 15));
		LineTo(hdc, int(m_tInfo.fX - 70 / 2 + 56 + m_fScrollX), int(m_tInfo.fY + 30 / 2 - 30));
		LineTo(hdc, int(m_tInfo.fX - 70 / 2 + 63 + m_fScrollX), int(m_tInfo.fY + 30 / 2 - 30 + 15));
		LineTo(hdc, int(m_tInfo.fX - 70 / 2 + 69 + m_fScrollX), int(m_tInfo.fY + 30 / 2 - 30));
		LineTo(hdc, int(m_tInfo.fX - 70 / 2 + 69 + m_fScrollX), int(m_tInfo.fY + 30 / 2 - 30 + 30));
		LineTo(hdc, int(m_tInfo.fX - 70 / 2 + m_fScrollX), int(m_tInfo.fY + 30 / 2 - 30 + 30));
		break;
	}
}

void CMonster::Release(void)
{
}

void CMonster::SetMBulletList(list<CObj*>* _pMBulletList)
{
	m_pMBulletList = _pMBulletList;
}

void CMonster::SetPlayer(CObj* _pPlayer)
{
	m_pPlayer = _pPlayer;
}