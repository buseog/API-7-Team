#pragma once

#include "define.h"

class CObj
{
protected:
	INFO		m_tInfo;
	float		m_fSpeed;
	float		m_fAngle;
	float		m_fDistance;

public:
	INFO		GetInfo(void);
	RECT		GetRect(void);
	void		SetPos(float _fX, float _fY);
	

public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(void)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CObj(void);
	virtual ~CObj(void);
};
