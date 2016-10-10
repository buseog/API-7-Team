#pragma once
#include "obj.h"
#include "MonBullet.h"

class CMonster :
	public CObj
{
private:
	int				m_iCollision;
	int				m_iType;
	list<CObj*>*	m_pMonBullet;
	list<CObj*>*	m_ListObj[OBJ_END];

public:
	void Initialize(void);
	void Progress(float _Time);		
	void Render(HDC hdc);	
	void Release(void);	
public:
	void SetMonBullet(list<CObj*>* _pMonBullet);
public:
	CMonster(void);
	CMonster(int _iInput);
	~CMonster(void);
};
