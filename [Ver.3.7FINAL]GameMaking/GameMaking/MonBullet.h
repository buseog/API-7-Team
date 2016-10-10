#pragma once
#include "obj.h"

class CMonBullet : public CObj
{
private:
	int		 m_iType;

public:
	virtual void Initialize(void);
	virtual void Progress(float _Time);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	void NomalType(void);
	void TargetType(void);
	void Razer(void);
	void RandomType(void);
public:
	CMonBullet(void);
	CMonBullet(int _iInput);
	~CMonBullet(void);
};