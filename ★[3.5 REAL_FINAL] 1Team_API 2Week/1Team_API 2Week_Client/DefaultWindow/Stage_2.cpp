#include "StdAfx.h"
#include "Stage_2.h"
#include "ObjFactory.h"
#include "Box.h"
#include "Player.h"
#include "Boss.h"
#include "Monster.h"
#include "CollisionMgr.h"
#include "Item.h"

CStage_2::CStage_2(void)
{
}

CStage_2::~CStage_2(void)
{
}

void CStage_2::Initialize(void)
{
	m_hdc = GetDC(g_hWnd);
	m_CTimer.SetTimer();

	((CPlayer*)m_ObjList[OBJ_PLAYER]->back())->SetLine(&m_LineList);
	
	LoadData();
	m_ObjList[OBJ_BOSS]->push_back(CObjFactory<CBoss>::CreateObj(3600.f, 100.f, BOSS_2));
	((CBoss*)m_ObjList[OBJ_BOSS]->back())->SetMBulletList(m_ObjList[OBJ_MONSTERBULLET]);
	m_ObjList[OBJ_ITEM]->push_back(CObjFactory<CItem>::CreateObj(430.f, 210.f, ITEM_RECOVERY));
	m_ObjList[OBJ_ITEM]->push_back(CObjFactory<CItem>::CreateObj(850.f, 35.f, ITEM_ATTACK));
	m_ObjList[OBJ_ITEM]->push_back(CObjFactory<CItem>::CreateObj(3060.f, 10.f, ITEM_ATTACK));
}
void CStage_2::Progress(float _fTime)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (list<CObj*>::iterator iter = m_ObjList[i]->begin(); iter != m_ObjList[i]->end(); ++iter)
		{
			(*iter)->Progress(_fTime);
		}
	}
	CCollisionMgr::CollisionMonster(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]);
	CCollisionMgr::CollisionBoss(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BOSS]);
	CCollisionMgr::CollisionWell(m_ObjList[OBJ_PLAYER]);
	CCollisionMgr::CollisionBox(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BOX]);	// 플레이어 박스타기
	CCollisionMgr::CollisionItem(m_ObjList[OBJ_ITEM], m_ObjList[OBJ_PLAYER]);	// 아이템먹기
	CCollisionMgr::CollisionMap(m_ObjList[OBJ_BULLET], m_LineList);				// 미사일 라인삭제
	CCollisionMgr::CollisionBox2(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_BOX]);	// 미사일 박스삭제
	CCollisionMgr::CollisionKinfe(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_PLAYER]);	//칼 사정거리
	CCollisionMgr::CollisionRange(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTERBULLET]);	//거리 나가면 삭제
	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_MONSTER]);	//미사일 몬스터충돌
	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_BULLET], m_ObjList[OBJ_BOSS]);		//미사일 보스충돌
	CCollisionMgr::CollisionAttack(m_ObjList[OBJ_MONSTERBULLET], m_ObjList[OBJ_PLAYER]);	// 몬스터총알 플레이어
	CCollisionMgr::CollisionBox2(m_ObjList[OBJ_MONSTERBULLET], m_ObjList[OBJ_BOX]);	//몬스터미사일 박스충돌
}
void CStage_2::Render(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (list<CObj*>::iterator Iter = m_ObjList[i]->begin(); Iter != m_ObjList[i]->end(); ++Iter)
		{
			(*Iter)->Render(m_hdc);
		}
	}

	if (m_LineList.size() != 0)
	{
		MoveToEx(m_hdc, 
		int(m_LineList.front()->tLPoint.fX + CObj::GetScrollX()), 
		(int)m_LineList.front()->tLPoint.fY, NULL);

		for(list<LINE*>::iterator	iter = m_LineList.begin();
			iter != m_LineList.end(); ++iter)
		{
			LineTo(m_hdc, int((*iter)->tRPoint.fX), (int)(*iter)->tRPoint.fY);
		}
	}
	if (m_RecList.size() != 0)
	{
		for (list<LINE*>::iterator	iter = m_RecList.begin();
			iter != m_RecList.end(); ++iter)
		{
			Rectangle(m_hdc, int((*iter)->tLPoint.fX + CObj::GetScrollX()), int((*iter)->tLPoint.fY), int((*iter)->tRPoint.fX + CObj::GetScrollX()), int((*iter)->tRPoint.fY));
		}
	}
}
void CStage_2::Release(void)
{
}

void CStage_2::SetObjList(int _iNum, list<CObj*>* _pObjList)
{
	m_ObjList[_iNum] = _pObjList;
}

int CStage_2::Stage_Clear(void)
{
	if(m_ObjList[OBJ_BOSS]->size() == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void CStage_2::LoadData(void)
{
	HANDLE		hFile = NULL;
	DWORD		dwByte = 0;

	hFile = CreateFile(L"../Data/line2.dat", 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	while(true)
	{
		LINE*		pLine = new LINE;

		ReadFile(hFile, pLine, sizeof(LINE), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pLine);
			break;
		}
		m_LineList.push_back(pLine);
	}

	CloseHandle(hFile);

	hFile = CreateFile(L"../Data/Rec2.dat", 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	while(true)
	{
		LINE*		pLine = new LINE;

		ReadFile(hFile, pLine, sizeof(LINE), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pLine);
			break;
		}
		m_RecList.push_back(pLine);

		m_ObjList[OBJ_BOX]->push_back(CObjFactory<CBox>::CreateObj(100,200,0));
		((CBox*)m_ObjList[OBJ_BOX]->back())->SetPoint(m_RecList.back()->tLPoint.fX,m_RecList.back()->tLPoint.fY,
			m_RecList.back()->tRPoint.fX,m_RecList.back()->tRPoint.fY);
	}

	CloseHandle(hFile);


	//몬스터

	hFile = CreateFile(L"../Data/Mon21.dat",
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	while(true)
	{
		LINEPOINT*		pPoint = new LINEPOINT;

		ReadFile(hFile, pPoint, sizeof(LINEPOINT), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pPoint);
			break;
		}

		m_ObjList[OBJ_MONSTER]->push_back(CObjFactory<CMonster>::CreateObj(pPoint->fX,pPoint->fY, MONSTER_1));
		((CMonster*)m_ObjList[OBJ_MONSTER]->back())->SetMBulletList(m_ObjList[OBJ_MONSTERBULLET]);
		((CMonster*)m_ObjList[OBJ_MONSTER]->back())->SetPlayer(m_ObjList[OBJ_PLAYER]->back());
	}

	CloseHandle(hFile);

	//몬스터 2

	hFile = CreateFile(L"../Data/Mon22.dat",
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	while(true)
	{
		LINEPOINT*		pPoint = new LINEPOINT;

		ReadFile(hFile, pPoint, sizeof(LINEPOINT), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pPoint);
			break;
		}

		m_ObjList[OBJ_MONSTER]->push_back(CObjFactory<CMonster>::CreateObj(pPoint->fX,pPoint->fY, MONSTER_2));
		((CMonster*)m_ObjList[OBJ_MONSTER]->back())->SetMBulletList(m_ObjList[OBJ_MONSTERBULLET]);
		((CMonster*)m_ObjList[OBJ_MONSTER]->back())->SetPlayer(m_ObjList[OBJ_PLAYER]->back());
	}

	CloseHandle(hFile);

	//몬스터 3

	hFile = CreateFile(L"../Data/Mon23.dat",
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	while(true)
	{
		LINEPOINT*		pPoint = new LINEPOINT;

		ReadFile(hFile, pPoint, sizeof(LINEPOINT), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pPoint);
			break;
		}

		m_ObjList[OBJ_MONSTER]->push_back(CObjFactory<CMonster>::CreateObj(pPoint->fX,pPoint->fY, MONSTER_3));
		((CMonster*)m_ObjList[OBJ_MONSTER]->back())->SetMBulletList(m_ObjList[OBJ_MONSTERBULLET]);
		((CMonster*)m_ObjList[OBJ_MONSTER]->back())->SetPlayer(m_ObjList[OBJ_PLAYER]->back());
	}

	CloseHandle(hFile);
}