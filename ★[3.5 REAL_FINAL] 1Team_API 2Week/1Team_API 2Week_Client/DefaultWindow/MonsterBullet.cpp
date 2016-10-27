#include "StdAfx.h"
#include "MonsterBullet.h"

CMonsterBullet::CMonsterBullet(void)
{
}

CMonsterBullet::CMonsterBullet(int _iType)
{
	m_iType = _iType;
	m_fSpeed = 5.f;
}

CMonsterBullet::~CMonsterBullet(void)
{
}

void CMonsterBullet::Initialize(void)
{
	m_CTimer.SetTimer();


	switch (m_iType)
	{
	case BULLET_NORMAL:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 10.f, 10.f);
		m_tStat = STAT(2.f, 1.f, 5.f);
		break;

	case BULLET_KNIFE:
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 50.f, 50.f);
		m_tStat = STAT(2.f, 1.f, 5.f);
		break;

	case BULLET_BOSS_11:								//보스1몬스터총알추가
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 10.f, 10.f);
		m_tStat = STAT(2.f, 1.f, 5.f);
		break;
	case BULLET_BOSS_12:								//보스1몬스터총알추가
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 10.f, 10.f);
		m_tStat = STAT(2.f, 1.f, 5.f);
		break;

	case BULLET_BOSS_13:								//보스1몬스터총알추가
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 10.f, 10.f);
		m_tStat = STAT(2.f, 1.f, 5.f);
		break;

	case BULLET_BOSS_2:							  	    //보스2몬스터총알추가
		m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 10.f, 10.f);
		m_tStat = STAT(2.f, 1.f, 5.f);
		break;
	}
}

void CMonsterBullet::Progress(float _fTime)
{
	switch (m_iType)
	{
	case BULLET_NORMAL:
			m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * (2.f * m_fSpeed);
			m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * (2.f * m_fSpeed);
			//플레이어 위치값 가져와서 -1 곱하는것 추가
			break;
	case BULLET_BOSS_11:							//보스몬스터1 총알 추가
			m_tInfo.fY += 5.f;
			break;
	case BULLET_BOSS_12:							//보스몬스터1 총알 추가
			m_tInfo.fY += 5.f;
			m_tInfo.fX += 5.f;
			break;
	case BULLET_BOSS_13:							//보스몬스터1 총알 추가
			m_tInfo.fY += 5.f;
			m_tInfo.fX -= 5.f;
			break;
	case BULLET_BOSS_2:
			//m_fAngle += 10.f;
			m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * (2.f * m_fSpeed);
			m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * (2.f * m_fSpeed);
			//m_tInfo.fX -= m_fSpeed;  
			break;
	}
}

void CMonsterBullet::Render(HDC hdc)
{
	switch (m_iType)
	{
	case BULLET_NORMAL:
		Ellipse(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		break;
	case BULLET_BOSS_11:							//보스1몬스터총알 추가
		Ellipse(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		break;
	case BULLET_BOSS_12:							//보스1몬스터총알 추가
		Ellipse(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		break;
	case BULLET_BOSS_13:							//보스1몬스터총알 추가
		Ellipse(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		break;
	case BULLET_BOSS_2:							//보스2몬스터총알 추가
		Ellipse(hdc, 
		int(m_tInfo.fX - m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f + m_fScrollX),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f));
		break;
	}
}

void CMonsterBullet::Release(void)
{

}

