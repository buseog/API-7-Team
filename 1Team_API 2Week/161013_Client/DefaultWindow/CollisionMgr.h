#pragma once
#include "Obj.h"

class CCollisionMgr
{
public:
	static void CollisionSphere(list<CObj*>* pTemp, list<CObj*>* pDest);

public:
	CCollisionMgr(void);
	~CCollisionMgr(void);
};
