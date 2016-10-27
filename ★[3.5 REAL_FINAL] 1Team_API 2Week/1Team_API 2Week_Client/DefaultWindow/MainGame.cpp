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
	m_hdc = GetDC(g_hWnd); // HDC 가져오기.
	m_CTimer.SetTimer();
	m_iStage = 1;
	///////////Obj_List /////////////
	m_ObjList[OBJ_PLAYER].push_back(CObjFactory<CPlayer>::CreateObj(100,100,PLAYER_HUMAN));	// ObjLIst에서 플레이더 같이 관리함. 플레이어 생성(100,100위치에 PLAYER_HUMAN타입으로 생성)
	((CPlayer*)m_ObjList[OBJ_PLAYER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);		// ObjList에 있는 OBJ_BULLET을 Player클래스가 가진 BulletList랑 동기화시킴.

	///////////스테이지 //////////////////
	m_CStage1 = new CStage_1;		// 1스테이지를 활성화시킴.
	for (int i = 0; i < OBJ_END; ++i)	//포문 돌면서 ObjList 0~ END까지 전부 다 돌린다.(플레이어~박스까지)
	{
		((CStage_1*)m_CStage1)->SetObjList(i, &m_ObjList[i]); // 메인게임이 가진 ObjList를 스테이지 1이 가진 ObjList랑 동기화시킨다.
	}
	m_CStage1->Initialize();		// 1스테이지가 가진 이니셜라이즈
	
}

void CMainGame::Progress(float _fTime)
{
	switch (m_iStage)	// m_iStage는 현재 스테이지를 나타낸다. 플래그에 따라 다른 스테이지를 작동함.
	{
	case 1:
		m_CStage1->Progress(_fTime);
		m_iStage += m_CStage1->Stage_Clear();
		if (m_iStage == 2)
		{
			m_CStage2 = new CStage_2;		// 1스테이지를 활성화시킴.
	
			for (int i = 0; i < OBJ_END; ++i)	//포문 돌면서 ObjList 0~ END까지 전부 다 돌린다.(플레이어~박스까지)
			{
				((CStage_2*)m_CStage2)->SetObjList(i, &m_ObjList[i]); // 메인게임이 가진 ObjList를 스테이지 2가 가진 ObjList랑 동기화시킨다.
			}
		
			m_ObjList[OBJ_BOX].clear();
			m_ObjList[OBJ_MONSTER].clear();
			CObj::SetScrollX();
			((CPlayer*)m_ObjList[OBJ_PLAYER].back())->SetStageUp();
			m_CStage2->Initialize();		// 1스테이지가 가진 이니셜라이즈
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
	Rectangle(m_hdc, 0, 0, WINCX, WINCY);	// 화면 청소
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
	switch (m_iStage)	// m_iStage는 현재 스테이지를 나타낸다. 플래그에 따라 다른 스테이지를 출력함.
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
	
	for (int i = 0; i < OBJ_END; ++i)	// 0~ END 까지 돌면서 ObjList안의 모든 원소를 세이프 딜리트한다.
	{
		for (list<CObj*>::iterator Iter = m_ObjList[i].begin(); Iter != m_ObjList[i].end(); ++Iter)
		{
			Safe_Delete(*Iter);
		}
		m_ObjList[i].clear();		// 원소를 모두 비운 i번째의 ObjList를 메모리에서 없앤다.
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
		TextOut(m_hdc, WINCX / 2, 250, TEXT("시작하기 : ENTER"), 12);
		TextOut(m_hdc, WINCX / 2, 350, TEXT("종료하기 :  ESC "), 12);
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
		TextOut(m_hdc, WINCX / 2, 350, TEXT("종료하기 :  ESC "), 12);
		TextOut(m_hdc, WINCX / 2, 300, TEXT(" "), 1);
		break;

		
	case 3:
		Rectangle(m_hdc, 0, 0, WINCX, WINCY);
		SetTextAlign(m_hdc, TA_CENTER);
		TextOut(m_hdc, WINCX / 2, 250, TEXT("You Win !!"), 10);
		TextOut(m_hdc, WINCX / 2, 350, TEXT("종료하기 :  ESC "), 12);
		TextOut(m_hdc, WINCX / 2, 300, TEXT(" "), 1);
		break;
	}
}
int CMainGame::GetIntro(void)
{
	return m_iIntro;
}