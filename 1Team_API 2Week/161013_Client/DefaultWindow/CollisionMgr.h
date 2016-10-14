#pragma once
#include "Obj.h"

class CCollisionMgr
{
public:
	static void CollisionSphere(list<CObj*>* pTemp, list<CObj*>* pTemp2);
	static void CollisionBox(list<CObj*>* pTemp, list<CObj*>* pTemp2);

public:
	CCollisionMgr(void);
	~CCollisionMgr(void);
};
