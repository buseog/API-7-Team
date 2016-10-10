#pragma once
#include "obj.h"

class CBullet :
	public CObj
{
public:
	CBullet(void);
	~CBullet(void);

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
};
