#pragma once
#include "Timer.h"
#include "define.h"
#include <CTime>

class CObj
{
protected:
	CTimer		m_Timer;
	INFO		m_tInfo;
	STAT		m_tStat;
	HDC			m_hdc;
	float		fDX;
	float		fDY;

public:
	INFO GetInfo(void);
	STAT GetStat(void);
	void SetDamage(float _fAttack);
	void SetXY(float _fX, float _fY);
	void SetHp(float _fHp);
	void SetAttack(float _fAttack);
	void SetDestroy(void);
	void SetDXY(float _fX, float _fY);
	float GetfDX(void);
public:
	void StatRender(void);

public:
	
	virtual void Initialize(void)		PURE;
	virtual void Progress(float _Time)	PURE;
	virtual void Render(HDC hdc)		PURE;
	virtual void Release(void)			PURE;

public:
	CObj(void);
	CObj(int _iInput);
	virtual ~CObj(void);
};
