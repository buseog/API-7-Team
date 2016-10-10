#pragma once
#include "obj.h"

class CMonster :
	public CObj
{
public:
	CMonster(void);
	~CMonster(void);

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
};
