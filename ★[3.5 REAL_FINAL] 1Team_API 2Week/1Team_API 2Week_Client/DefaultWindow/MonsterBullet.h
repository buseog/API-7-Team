#pragma once
#include "obj.h"

class CMonsterBullet :
	public CObj
{
private:
	float m_fSpeed;
public:
	virtual void Initialize(void);
	virtual void Progress(float _fTime);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CMonsterBullet(void);
	CMonsterBullet(int _iType);
	~CMonsterBullet(void);
};
