#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "ObjFactory.h"
#include "Stage_1.h"
#include "Stage_2.h"

CMainGame::CMainGame(void)
:m_iStage(1)
{

}

CMainGame::~CMainGame(void)
{
	Release();
}

void CMainGame::LoadData(void)
{
	HANDLE		hFile = NULL;
	DWORD		dwByte = 0;

	hFile = CreateFile(L"../Data/line.dat", 
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
}

void CMainGame::Initialize(void)
{
	m_hdc = GetDC(g_hWnd); // HDC 가져오기.
	m_CTimer.SetTimer();

	/////////Obj_List /////////////
	m_ObjList[OBJ_PLAYER].push_back(CObjFactory<CPlayer>::CreateObj(100,100,PLAYER_HUMAN));	// ObjLIst에서 플레이더 같이 관리함. 플레이어 생성(100,100위치에 PLAYER_HUMAN타입으로 생성)
	((CPlayer*)m_ObjList[OBJ_PLAYER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);		// ObjList에 있는 OBJ_BULLET을 Player클래스가 가진 BulletList랑 동기화시킴.
	

	/////// 맵툴 /////// ★★잠시보류★★
	LoadData();	// 맵 불러오기
	((CPlayer*)m_ObjList[OBJ_PLAYER].back())->SetLine(&m_LineList);	// 플레이어가 가진 라인이랑 동기화


	///////////스테이지 //////////////////
	m_CStage1 = new CStage_1;		// 1스테이지를 활성화시킴.
	m_CStage1->Initialize();		// 1스테이지가 가진 이니셜라이즈
	((CStage_1*)m_CStage1)->SetLineList(&m_LineList);
	for (int i = 0; i < OBJ_END; ++i)	//포문 돌면서 ObjList 0~ END까지 전부 다 돌린다.(플레이어~박스까지)
	{
		((CStage_1*)m_CStage1)->SetObjList(i, &m_ObjList[i]); // 메인게임이 가진 ObjList를 스테이지 1이 가진 ObjList랑 동기화시킨다.
	}

	m_CStage2 = new CStage_2;		// 1스테이지를 활성화시킴.
	m_CStage2->Initialize();		// 1스테이지가 가진 이니셜라이즈
	for (int i = 0; i < OBJ_END; ++i)	//포문 돌면서 ObjList 0~ END까지 전부 다 돌린다.(플레이어~박스까지)
	{
		((CStage_2*)m_CStage2)->SetObjList(i, &m_ObjList[i]); // 메인게임이 가진 ObjList를 스테이지 1이 가진 ObjList랑 동기화시킨다.
	}
}

void CMainGame::Progress(float _fTime)
{
	switch (m_iStage)	// m_iStage는 현재 스테이지를 나타낸다. 플래그에 따라 다른 스테이지를 작동함.
	{
	case 1:
		m_CStage1->Progress(_fTime);
		m_iStage += m_CStage1->Stage_Clear();
		break;
	case 2:
		m_CStage2->Progress(_fTime);
		m_iStage += m_CStage2->Stage_Clear();
		break;
	case 3:
		break;
	}
}

void CMainGame::Render(void)
{
	Rectangle(m_hdc, 0, 0, WINCX, WINCY);	// 화면 청소

	switch (m_iStage)	// m_iStage는 현재 스테이지를 나타낸다. 플래그에 따라 다른 스테이지를 출력함.
	{
	case 1:
		m_CStage1->Render();
		break;
	case 2:
		m_CStage2->Render();
		break;
	case 3:
		break;
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
}


