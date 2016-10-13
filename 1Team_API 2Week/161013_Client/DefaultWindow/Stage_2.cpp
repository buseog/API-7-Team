#include "StdAfx.h"
#include "Stage_2.h"

CStage_2::CStage_2(void)
{
}

CStage_2::~CStage_2(void)
{
}

void CStage_2::Initialize(void)
{
	m_hdc = GetDC(g_hWnd);
}
void CStage_2::Progress(float _fTime)
{
}
void CStage_2::Render(void)
{
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
	if(1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}