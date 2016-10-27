#pragma once
#include "Obj.h"

class CCollisionMgr
{
public:
	static void CollisionRange(list<CObj*>* pTemp, list<CObj*>* pTemp2);
	static void CollisionBox(list<CObj*>* pTemp, list<CObj*>* pTemp2);
	static void CollisionBox2(list<CObj*>* pTemp, list<CObj*>* pTemp2);
	static void CollisionMap(list<CObj*>* pBullet, list<LINE*> pMap);
	static void CollisionItem(list<CObj*>* pItem, list<CObj*>* pPlayer);
	static void CollisionAttack(list<CObj*>* pTemp, list<CObj*>* pTemp2);
	static void CollisionKinfe(list<CObj*>* pBullet, list<CObj*>* pPlayer);
	static void CollisionWell(list<CObj*>* pPlayer);
	static void	CollisionMonster(list<CObj*>* pPlayer, list<CObj*>* pMonster);
	static void CollisionBoss(list<CObj*>* pPlayer, list<CObj*>* pBoss);
public:
	CCollisionMgr(void);
	~CCollisionMgr(void);
};
