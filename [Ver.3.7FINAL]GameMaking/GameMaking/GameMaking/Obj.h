#pragma once

#include "define.h"

class CObj
{
protected:
	INFO		m_tInfo;
	float		m_fSpeed;
	
public:
	INFO		GetInfo(void);
	void		SetPos(float _fX, float _fY);
	RECT		GetRect(void);

public:
	virtual void Initialize(void)	PURE;
	virtual void Progress(void)		PURE;
	virtual void Render(HDC hdc)	PURE;
	virtual void Release(void)		PURE;

public:
	CObj(void);
	virtual ~CObj(void);
};
