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
	m_hdc = GetDC(g_hWnd); // HDC ��������.
	m_CTimer.SetTimer();

	/////////Obj_List /////////////
	m_ObjList[OBJ_PLAYER].push_back(CObjFactory<CPlayer>::CreateObj(100,100,PLAYER_HUMAN));	// ObjLIst���� �÷��̴� ���� ������. �÷��̾� ����(100,100��ġ�� PLAYER_HUMANŸ������ ����)
	((CPlayer*)m_ObjList[OBJ_PLAYER].back())->SetBulletList(&m_ObjList[OBJ_BULLET]);		// ObjList�� �ִ� OBJ_BULLET�� PlayerŬ������ ���� BulletList�� ����ȭ��Ŵ.
	

	/////// ���� /////// �ڡ���ú����ڡ�
	LoadData();	// �� �ҷ�����
	((CPlayer*)m_ObjList[OBJ_PLAYER].back())->SetLine(&m_LineList);	// �÷��̾ ���� �����̶� ����ȭ


	///////////�������� //////////////////
	m_CStage1 = new CStage_1;		// 1���������� Ȱ��ȭ��Ŵ.
	m_CStage1->Initialize();		// 1���������� ���� �̴ϼȶ�����
	((CStage_1*)m_CStage1)->SetLineList(&m_LineList);
	for (int i = 0; i < OBJ_END; ++i)	//���� ���鼭 ObjList 0~ END���� ���� �� ������.(�÷��̾�~�ڽ�����)
	{
		((CStage_1*)m_CStage1)->SetObjList(i, &m_ObjList[i]); // ���ΰ����� ���� ObjList�� �������� 1�� ���� ObjList�� ����ȭ��Ų��.
	}

	m_CStage2 = new CStage_2;		// 1���������� Ȱ��ȭ��Ŵ.
	m_CStage2->Initialize();		// 1���������� ���� �̴ϼȶ�����
	for (int i = 0; i < OBJ_END; ++i)	//���� ���鼭 ObjList 0~ END���� ���� �� ������.(�÷��̾�~�ڽ�����)
	{
		((CStage_2*)m_CStage2)->SetObjList(i, &m_ObjList[i]); // ���ΰ����� ���� ObjList�� �������� 1�� ���� ObjList�� ����ȭ��Ų��.
	}
}

void CMainGame::Progress(float _fTime)
{
	switch (m_iStage)	// m_iStage�� ���� ���������� ��Ÿ����. �÷��׿� ���� �ٸ� ���������� �۵���.
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
	Rectangle(m_hdc, 0, 0, WINCX, WINCY);	// ȭ�� û��

	switch (m_iStage)	// m_iStage�� ���� ���������� ��Ÿ����. �÷��׿� ���� �ٸ� ���������� �����.
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
}


