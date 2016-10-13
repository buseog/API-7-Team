#pragma once
#include "obj.h"

class CBoss :
	public CObj
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
public:
	CBoss(void);
	CBoss(int _iType);
	~CBoss(void);
};
