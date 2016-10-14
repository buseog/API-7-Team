#include "StdAfx.h"
#include "Stage_1.h"
#include "ObjFactory.h"
#include "Box.h"
#include "CollisionMgr.h"


CStage_1::CStage_1(void)
{
}

CStage_1::~CStage_1(void)
{
}

void CStage_1::Initialize(void)
{
	m_hdc = GetDC(g_hWnd);
	m_CTimer.SetTimer();
	m_ObjList[OBJ_BOX]->push_back(CObjFactory<CBox>::CreateObj(200.f, 200.f, BOX_NORMAL));
}
void CStage_1::Progress(float _fTime)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (list<CObj*>::iterator Iter = m_ObjList[i]->begin(); Iter != m_ObjList[i]->end(); ++Iter)
		{
			(*Iter)->Progress();
		}
	}

	CCollisionMgr::CollisionBox(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_BOX]);
}
void CStage_1::Render(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (list<CObj*>::iterator Iter = m_ObjList[i]->begin(); Iter != m_ObjList[i]->end(); ++Iter)
		{
			(*Iter)->Render(m_hdc);
		}
	}

	MoveToEx(m_hdc, 
	int(m_LineList->front()->tLPoint.fX + CObj::GetScrollX()), 
	(int)m_LineList->front()->tLPoint.fY, NULL);

	for(list<LINE*>::iterator	iter = m_LineList->begin();
		iter != m_LineList->end(); ++iter)
	{
		LineTo(m_hdc, int((*iter)->tRPoint.fX + CObj::GetScrollX()), (int)(*iter)->tRPoint.fY);
	}
}
void CStage_1::Release(void)
{
}


void CStage_1::SetObjList(int _iNum, list<CObj*>* _pObjList)
{
	m_ObjList[_iNum] = _pObjList;
}

void CStage_1::SetLineList(list<LINE*>* _pLineList)
{
	m_LineList = _pLineList;
}

int CStage_1::Stage_Clear(void)
{
	if(0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}