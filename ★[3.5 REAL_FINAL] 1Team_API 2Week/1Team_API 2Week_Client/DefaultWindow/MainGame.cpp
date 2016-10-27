#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "ObjFactory.h"
#include "Stage_1.h"
#include "Stage_2.h"
#include "Monster.h"
#include "Boss.h"

CMainGame::CMainGame(void)
:m_iStage(1)
,m_iIntro(1)
,m_CStage1(NULL)
,m_CStage2(NULL)
{

}

CMainGame::~CMainGame(void)
{
	Release();
}

void CMainGame::LoadData(void)
{
}

void CMainGame::Initialize(void)
{
	m_hdc = GetDC(g_hWnd); // HDC ��������.
	m_CTimer.SetTimer();
	m_iStage = 1;
	///////////Obj_List /////////////
	m_ObjList[OBJ_PLAYER].push_back(CObjFactory<CPlayer>::CreateObj(100,100,PLAYER_HUMAN));	// ObjLIst���� �÷��̴� ���� ������. �÷��̾� ����(100,100��ġ�� PLAYER_HUMANŸ������ ����)
	((CPlayer*)m_ObjList[OBJ_PLAYER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);		// ObjList�� �ִ� OBJ_BULLET�� PlayerŬ������ ���� BulletList�� ����ȭ��Ŵ.

	///////////�������� //////////////////
	m_CStage1 = new CStage_1;		// 1���������� Ȱ��ȭ��Ŵ.
	for (int i = 0; i < OBJ_END; ++i)	//���� ���鼭 ObjList 0~ END���� ���� �� ������.(�÷��̾�~�ڽ�����)
	{
		((CStage_1*)m_CStage1)->SetObjList(i, &m_ObjList[i]); // ���ΰ����� ���� ObjList�� �������� 1�� ���� ObjList�� ����ȭ��Ų��.
	}
	m_CStage1->Initialize();		// 1���������� ���� �̴ϼȶ�����
	
}

void CMainGame::Progress(float _fTime)
{
	switch (m_iStage)	// m_iStage�� ���� ���������� ��Ÿ����. �÷��׿� ���� �ٸ� ���������� �۵���.
	{
	case 1:
		m_CStage1->Progress(_fTime);
		m_iStage += m_CStage1->Stage_Clear();
		if (m_iStage == 2)
		{
			m_CStage2 = new CStage_2;		// 1���������� Ȱ��ȭ��Ŵ.
	
			for (int i = 0; i < OBJ_END; ++i)	//���� ���鼭 ObjList 0~ END���� ���� �� ������.(�÷��̾�~�ڽ�����)
			{
				((CStage_2*)m_CStage2)->SetObjList(i, &m_ObjList[i]); // ���ΰ����� ���� ObjList�� �������� 2�� ���� ObjList�� ����ȭ��Ų��.
			}
		
			m_ObjList[OBJ_BOX].clear();
			m_ObjList[OBJ_MONSTER].clear();
			CObj::SetScrollX();
			((CPlayer*)m_ObjList[OBJ_PLAYER].back())->SetStageUp();
			m_CStage2->Initialize();		// 1���������� ���� �̴ϼȶ�����
		}
		break;
	case 2:
		m_CStage2->Progress(_fTime);
		m_iStage += m_CStage2->Stage_Clear();
		if (m_iStage == 3)
		{
			m_iIntro = 3;
		}
		break;
	case 3:
		return;
	}

	if (m_ObjList[OBJ_PLAYER].size() == 0)
	{
		m_iIntro = 2;
	}
}

void CMainGame::Render(void)
{
	Rectangle(m_hdc, 0, 0, WINCX, WINCY);	// ȭ�� û��
	Rectangle(m_hdc, 0, 500, 200, 600);
	switch (m_iStage)
	{
	case 1:
		TextOut(m_hdc, 75, 567, TEXT("STAGE 1"), 7);
		break;

	case 2:
		TextOut(m_hdc, 75, 567, TEXT("STAGE 2"), 7);
		break;

	case 3:
		TextOut(m_hdc, 75, 567, TEXT("STAGE 3"), 7);
		break;
	}
	switch (m_iStage)	// m_iStage�� ���� ���������� ��Ÿ����. �÷��׿� ���� �ٸ� ���������� �����.
	{
	case 1:
		m_CStage1->Render();
		break;
	case 2:
		m_CStage2->Render();
		break;
	case 3:
		return;
	}

	
}

void CMainGame::Release(void)
{
	ReleaseDC(g_hWnd, m_hdc);
	
	for (int i = 0; i < OBJ_END; ++i)	// 0~ END ���� ���鼭 ObjList���� ��� ���Ҹ� ������ ����Ʈ�Ѵ�.
	{
		for (list<CObj*>::iterator Iter = m_ObjList[i].begin(); Iter != m_ObjList[i].end(); ++Iter)
		{
			Safe_Delete(*Iter);
		}
		m_ObjList[i].clear();		// ���Ҹ� ��� ��� i��°�� ObjList�� �޸𸮿��� ���ش�.
	}
	

	for(list<LINE*>::iterator	iter = m_LineList.begin();
		iter != m_LineList.end(); ++iter)
	{
		::Safe_Delete(*iter);
	}
	m_LineList.clear();

	Safe_Delete(m_CStage1);
	Safe_Delete(m_CStage2);
}


void CMainGame::Intro(void)
{
	switch (m_iIntro)
	{
	case 1:
		Rectangle(m_hdc, 0, 0, WINCX, WINCY);
		SetTextAlign(m_hdc, TA_CENTER);
		TextOut(m_hdc, WINCX / 2, 250, TEXT("�����ϱ� : ENTER"), 12);
		TextOut(m_hdc, WINCX / 2, 350, TEXT("�����ϱ� :  ESC "), 12);
		TextOut(m_hdc, WINCX / 2, 300, TEXT(" "), 1);
		
		if (GetAsyncKeyState(VK_RETURN))
		{
			m_iIntro = 0;
		}
		break;

	case 2:
		Rectangle(m_hdc, 0, 0, WINCX, WINCY);
		SetTextAlign(m_hdc, TA_CENTER);
		TextOut(m_hdc, WINCX / 2, 250, TEXT("Game Over !!"), 12);
		TextOut(m_hdc, WINCX / 2, 350, TEXT("�����ϱ� :  ESC "), 12);
		TextOut(m_hdc, WINCX / 2, 300, TEXT(" "), 1);
		break;

		
	case 3:
		Rectangle(m_hdc, 0, 0, WINCX, WINCY);
		SetTextAlign(m_hdc, TA_CENTER);
		TextOut(m_hdc, WINCX / 2, 250, TEXT("You Win !!"), 10);
		TextOut(m_hdc, WINCX / 2, 350, TEXT("�����ϱ� :  ESC "), 12);
		TextOut(m_hdc, WINCX / 2, 300, TEXT(" "), 1);
		break;
	}
}
int CMainGame::GetIntro(void)
{
	return m_iIntro;
}