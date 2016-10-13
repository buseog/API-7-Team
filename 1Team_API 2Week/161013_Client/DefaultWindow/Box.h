#pragma once
#include "obj.h"

class CBox :
	public CObj
{
public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);	
public:
	CBox(void);
	CBox(int _iType);
	~CBox(void);
};
