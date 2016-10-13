#pragma once
#include "obj.h"

class CItem :
	public CObj
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
public:
	CItem(void);
	CItem(int _iType);
	~CItem(void);
};
