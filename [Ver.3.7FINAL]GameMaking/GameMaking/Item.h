#pragma once
#include "obj.h"

class CItem :
	public CObj
{
private:
	int	 m_iType;

public:
	virtual void Initialize(void);
	virtual void Progress(float _Time);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	
public:
	void NomalType(void);
	void TargetType(void);

public:
	CItem(void);
	CItem(int _iInput);
	~CItem(void);
};
