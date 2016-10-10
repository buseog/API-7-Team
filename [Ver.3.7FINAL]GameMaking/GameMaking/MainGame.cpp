#include "StdAfx.h"
#include "MainGame.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Player.h"
#include "Monster.h"

CMainGame::CMainGame(void)
{
}

CMainGame::~CMainGame(void)
{
	Release();
}

void CMainGame::Initialize(void)	
{	
	m_hdc = GetDC(g_hWnd);

	m_Stage = 1;
	m_iIntro = 1;


	m_ListObj[OBJ_PLAYER].push_back(new CPlayer);
	m_ListObj[OBJ_PLAYER].back()->Initialize();
	((CPlayer*)m_ListObj[OBJ_PLAYER].back())->SetBulletList(&m_ListObj[OBJ_BULLET]);


	Stage1 = new CStage1;
	for (int i = 0; i < OBJ_END; ++i)
	{
		((CStage1*)Stage1)->SetListObj(i, &m_ListObj[i]);
	}
	Stage1->Initialize();


	Stage2 = new CStage2;
	for (int i = 0; i < OBJ_END; ++i)
	{
		((CStage2*)Stage2)->SetListObj(i, &m_ListObj[i]);
	}
	Stage2->Initialize();


	Stage3 = new CStage3;
	for (int i = 0; i < OBJ_END; ++i)
	{
		((CStage3*)Stage3)->SetListObj(i, &m_ListObj[i]);
	}	
	Stage3->Initialize();
	
}

void CMainGame::Progress(float _Time)
{
	if (GetAsyncKeyState(VK_F5))
	{
		m_iIntro = 2;
	}
	if (m_ListObj[OBJ_PLAYER].empty())
	{
		m_iIntro = 3;
		return;
	}
	switch (m_Stage)
	{
	case 1:
		Stage1->Progress(_Time);
		m_Stage += Stage1->Clear();
		if(Stage1->Clear() == 1)
		{
			m_iIntro = 5;
		}
		break;

	case 2:
		Stage2->Progress(_Time);
		m_Stage += Stage2->Clear();
		if(Stage2->Clear() == 1)
		{
			m_iIntro = 5;
		}
		break;
		
	case 3:
		Stage3->Progress(_Time);
		m_Stage += Stage3->Clear();
		if(Stage3->Clear() == 1)
		{
			m_iIntro = 4;
		}
		break;
	case 4:
		Intro();
		break;
	}
}

void CMainGame::Render(void)
{
	if (m_ListObj[OBJ_PLAYER].empty())
	{
		m_iIntro = 3;
		return;
	}
	Rectangle(m_hdc, 0, 0, WINCX, WINCY);
	Rectangle(m_hdc, 0, 0, 150, WINCY);
	TextRender(m_hdc);
	StatRender(m_hdc);

	switch (m_Stage)
	{
	case 1:
		Stage1->Render();
		break;
	case 2:
		Stage2->Render();
		break;
	case 3:
		Stage3->Render();
		break;
	case 4:
		Intro();
		break;

	}
}

void CMainGame::TextRender(HDC hdc)
{
	Rectangle(hdc, 0, 0, 150, WINCY);
	SetTextAlign(hdc, TA_CENTER);
	
	TextOut(hdc, 75, 20, TEXT("Shooting Game"), 13);
	
	MoveToEx(hdc, 0, 50, NULL);
	LineTo(hdc, 150, 50);
	TextOut(hdc, 75, 68, TEXT("미사일 종류"), 6);

	Rectangle(hdc, 10, 100, 40, 130);
	TextOut(hdc, 25, 107, TEXT("F1"), 2);
	TextOut(hdc, 90, 107, TEXT("일반 미사일"), 6);

	Rectangle(hdc, 10, 150, 40, 180);
	TextOut(hdc, 25, 157, TEXT("F2"), 2);
	TextOut(hdc, 90, 157, TEXT("유도탄"), 3);

	Rectangle(hdc, 10, 200, 40, 230);
	TextOut(hdc, 25, 207, TEXT("F3"), 2);
	TextOut(hdc, 90, 207, TEXT("지뢰"), 2);

	Rectangle(hdc, 10, 250, 40, 280);
	TextOut(hdc, 25, 257, TEXT("F4"), 2);
	TextOut(hdc, 90, 257, TEXT("산탄"), 2);



	MoveToEx(hdc, 0, 300, NULL);
	LineTo(hdc, 150, 300);
	TextOut(hdc, 75, 320, TEXT("능력치"), 3);



	for(list<CObj*>::iterator iter = m_ListObj[OBJ_PLAYER].begin(); 
		iter != m_ListObj[OBJ_PLAYER].end(); ++iter)
	{
		wchar_t wcTmp[128];
		RECT rc = {60, 350, 150, 490};
		TextOut(hdc, 40, 350, TEXT("공격력"), 3);
		swprintf(wcTmp, 128, L"%.f", (*iter)->GetStat().fAttack);
		DrawText(m_hdc, wcTmp, lstrlen(wcTmp), &rc, DT_CENTER);
	}
		
	
	for(list<CObj*>::iterator iter = m_ListObj[OBJ_PLAYER].begin(); 
		iter != m_ListObj[OBJ_PLAYER].end(); ++iter)
	{
		wchar_t wcTmp[128];
		RECT rc = {60, 400, 150, 490};
		TextOut(hdc, 40, 400, TEXT("이동속도"), 4);
		swprintf(wcTmp, 128, L"%.f", (*iter)->GetStat().fSpeed);
		DrawText(m_hdc, wcTmp, lstrlen(wcTmp), &rc, DT_CENTER);
	}

	MoveToEx(hdc, 0, 550, NULL);
	LineTo(hdc, 150, 550);
	switch(m_Stage)
	{
		case 1:
			TextOut(hdc, 75, 567, TEXT("STAGE 1"), 7);
			break;

		case 2:
			TextOut(hdc, 75, 567, TEXT("STAGE 2"), 7);
			break;

		case 3:
			TextOut(hdc, 75, 567, TEXT("STAGE 3"), 7);
			break;
	}

	switch (((CPlayer*)(m_ListObj[OBJ_PLAYER]).back())->GetBulletType())
	{
		case 1:
		{
			HPEN myPen	= CreatePen(PS_SOLID, 3, 0XCA2222);
			HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

			Rectangle(hdc, 10, 100, 40, 130);
			TextOut(hdc, 25, 107, TEXT("F1"), 2);
			TextOut(hdc, 90, 107, TEXT("일반 미사일"), 6);

			SelectObject(hdc, oldPen);	 
			DeleteObject(myPen);
			break;
		}

		case 2:
		{
			HPEN myPen	= CreatePen(PS_SOLID, 3, 0XCA2222);
			HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
	
			Rectangle(hdc, 10, 150, 40, 180);
			TextOut(hdc, 25, 157, TEXT("F2"), 2);
			TextOut(hdc, 90, 157, TEXT("유도탄"), 3);

			SelectObject(hdc, oldPen);	 
			DeleteObject(myPen);
			break;
		}

		case 3:
		{
			HPEN myPen	= CreatePen(PS_SOLID, 3, 0XCA2222);
			HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
	
			Rectangle(hdc, 10, 200, 40, 230);
			TextOut(hdc, 25, 207, TEXT("F3"), 2);
			TextOut(hdc, 90, 207, TEXT("지뢰"), 2);

			SelectObject(hdc, oldPen);	 
			DeleteObject(myPen);
			break;
		}

		case 4:
		{
			HPEN myPen	= CreatePen(PS_SOLID, 3, 0XCA2222);
			HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
	
			Rectangle(hdc, 10, 250, 40, 280);
			TextOut(hdc, 25, 257, TEXT("F4"), 2);
			TextOut(hdc, 90, 257, TEXT("산탄"), 2);

			SelectObject(hdc, oldPen);	 
			DeleteObject(myPen);
			break;
		}


	}
}

void CMainGame::StatRender(HDC hdc)
{
	HPEN myPen	= CreatePen(PS_SOLID, 1, 0X000000);
	HPEN oldPen = (HPEN)SelectObject(hdc, myPen);

	MoveToEx(hdc, 0, 500, NULL);
	LineTo(hdc, 150, 500);
	TextOut(hdc, 15, 517, TEXT("HP"), 2);
	m_hdc = GetDC(g_hWnd);
	RECT rc = {50, 517, 150, 540};
	wchar_t wcTmp[128];

	for(list<CObj*>::iterator iter = m_ListObj[OBJ_PLAYER].begin(); 
		iter != m_ListObj[OBJ_PLAYER].end(); ++iter)
	{
		swprintf(wcTmp, 128, L"%.f / %.f", (*iter)->GetStat().fHp, (*iter)->GetStat().fFullHp);

		if((*iter)->GetStat().fHp <= 0)
		{
			swprintf(wcTmp, 128, L"0 / %.f", (*iter)->GetStat().fFullHp);
		}
	}

	DrawText(m_hdc, wcTmp, lstrlen(wcTmp), &rc, DT_CENTER);

	SelectObject(hdc, oldPen);	 
	DeleteObject(myPen);
}

void CMainGame::SetPlayer(CObj* _pPlayer)
{
	m_pPlayer = _pPlayer;
}



void CMainGame::Intro(void)
{
	if (m_iIntro == 1)
	{
		Rectangle(m_hdc, 0, 0, WINCX, WINCY);
		SetTextAlign(m_hdc, TA_CENTER);
		TextOut(m_hdc, WINCX / 2, 250, TEXT("시작하기 : ENTER"), 12);
		TextOut(m_hdc, WINCX / 2, 350, TEXT("종료하기 :  ESC "), 12);
		TextOut(m_hdc, WINCX / 2, 300, TEXT(" "), 1);
		
		if (GetAsyncKeyState(VK_RETURN))
		{
			m_iIntro = 0;
		}
	}
	else if (m_iIntro == 2)
	{
		Rectangle(m_hdc, 0, 0, WINCX, WINCY);
		SetTextAlign(m_hdc, TA_CENTER);
		TextOut(m_hdc, WINCX / 2, 200, TEXT("일시 정지중!"), 6);
		TextOut(m_hdc, WINCX / 2, 250, TEXT("정지해제 : ENTER"), 12);
		TextOut(m_hdc, WINCX / 2, 350, TEXT("종료하기 :  ESC "), 12);
		TextOut(m_hdc, WINCX / 2, 300, TEXT(" "), 1);
	
		if (GetAsyncKeyState(VK_RETURN))
		{
			m_iIntro = 0;
		}
	}
	else if (m_iIntro == 3)
	{
		Rectangle(m_hdc, 0, 0, WINCX, WINCY);
		SetTextAlign(m_hdc, TA_CENTER);
		TextOut(m_hdc, WINCX / 2, 200, TEXT("  GAME OVER  !  "), 12);
		TextOut(m_hdc, WINCX / 2, 350, TEXT("종료하기 :  ESC "), 12);
		TextOut(m_hdc, WINCX / 2, 300, TEXT(" "), 1);
	}
	
	else if (m_iIntro == 4)
	{
		Rectangle(m_hdc, 0, 0, WINCX, WINCY);
		SetTextAlign(m_hdc, TA_CENTER);
		TextOut(m_hdc, WINCX / 2, 200, TEXT("  YOU WIN !!    "), 12);
		TextOut(m_hdc, WINCX / 2, 350, TEXT("종료하기 :  ESC "), 12);
		TextOut(m_hdc, WINCX / 2, 300, TEXT(" "), 1);
	}

	else if (m_iIntro == 5)
	{
		Rectangle(m_hdc, 0, 0, WINCX, WINCY);
		SetTextAlign(m_hdc, TA_CENTER);
		TextOut(m_hdc, WINCX / 2, 250, TEXT("다음스테이지 : ENTER"), 14);
		TextOut(m_hdc, WINCX / 2, 350, TEXT("종료하기 :  ESC "), 12);
		TextOut(m_hdc, WINCX / 2, 300, TEXT(" "), 1);
		
		if (GetAsyncKeyState(VK_RETURN))
		{
			m_iIntro = 0;
		}
	}
}

void CMainGame::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (list<CObj*>::iterator Iter = m_ListObj[i].begin(); Iter != m_ListObj[i].end(); ++Iter)
		{
			::Safe_Delete(*Iter);
		}
		m_ListObj[i].clear();
	}

}

int	CMainGame::GetIntro(void)
{
	return m_iIntro;
}