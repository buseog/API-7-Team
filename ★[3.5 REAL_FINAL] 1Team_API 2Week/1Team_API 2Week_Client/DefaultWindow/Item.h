#pragma once
#include "obj.h"

class CItem :
	public CObj
{
private:
	TCHAR			m_szHp[128];

public:
	virtual void Initialize(void);
	virtual void Progress(float _fTime);
	virtual void Render(HDC hdc);
	virtual void Release(void);
public:
	CItem(void);
	CItem(int _iType);
	~CItem(void);
};
