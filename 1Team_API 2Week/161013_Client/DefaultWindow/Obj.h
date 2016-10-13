#pragma once

#include "define.h"

class CObj
{
protected:
	INFO	m_tInfo;
	STAT	m_tStat;
	int		m_iType;
	static	float	m_fScrollX;

public:
	INFO	GetInfo(void);
	STAT	GetStat(void);
	RECT	GetRect(void);
	void	SetPos(float _fX, float _fY);
	void	SetDamage(float _fAttack);
	static float	GetScrollX(void);
	

public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(void)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CObj(void);
	CObj(int _iType);
	virtual ~CObj(void);
};
