#pragma once

#include "define.h"
#include "Timer.h"
class CObj
{
protected:
	CTimer	m_CTimer;
	INFO	m_tInfo;
	STAT	m_tStat;
	int		m_iType;
	float	m_fAngle;
	static	float	m_fScrollX;

public:
	INFO	GetInfo(void);
	STAT	GetStat(void);
	RECT	GetRect(void);
	int     GetType(void);
	void	SetPos(float _fX, float _fY);
	void	SetDamage(float _fAttack);
	void	SetAngle(float _fAngle);
	void    SetHP(float _fHP);
	void    SetType(int m_iType);
	static void	SetScrollX(void);
	static float GetScrollX(void);
	

public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(float _fTime)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CObj(void);
	CObj(int _iType);
	virtual ~CObj(void);
};
