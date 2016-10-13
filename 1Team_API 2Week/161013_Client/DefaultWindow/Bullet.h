#pragma once
#include "obj.h"

class CBullet :
	public CObj
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CBullet(void);
	CBullet(int _iType);
	~CBullet(void);
};
