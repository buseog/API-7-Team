#include "stdafx.h"
#include "MainGame.h"
#include "MyEdit.h"
#include "ObjFactory.h"

CMainGame::CMainGame(void)
: m_pMyEdit(NULL)
{

}

CMainGame::~CMainGame(void)
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hdc = GetDC(g_hWnd);

	m_pMyEdit = CObjFactory<CMyEdit>::CreateObj();
}

void CMainGame::Progress(void)
{
	m_pMyEdit->Progress();	
}

void CMainGame::Render(void)
{
	Rectangle(m_hdc, 0, 0, WINCX, WINCY);

	m_pMyEdit->Render(m_hdc);	
}

void CMainGame::Release(void)
{
	ReleaseDC(g_hWnd, m_hdc);

	::Safe_Delete(m_pMyEdit);
}


