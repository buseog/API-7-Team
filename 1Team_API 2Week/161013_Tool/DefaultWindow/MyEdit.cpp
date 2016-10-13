#include "StdAfx.h"
#include "MyEdit.h"



CMyEdit::CMyEdit(void)
{
}

CMyEdit::~CMyEdit(void)
{
	Release();
}

void CMyEdit::Initialize(void)
{
	m_bStart = false;
	m_fScrollX = 0.f;
	m_fSpeed = 10.f;
}

void CMyEdit::Progress(void)
{
	LINEPOINT		tMousePos;
	
	tMousePos.fX = (float)::GetMouse().x - m_fScrollX;
	tMousePos.fY = (float)::GetMouse().y;

	if(GetAsyncKeyState('S'))
	{
		m_tStartPoint = tMousePos;
		m_bStart = true;
	}

	if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if(m_bStart)
		{
			m_LineList.push_back(new LINE(m_tStartPoint, tMousePos));
			m_bStart = false;
		}

	m_LineList.push_back(new LINE(m_LineList.back()->tRPoint, tMousePos));
	}

	if(GetAsyncKeyState(VK_RETURN))
	{
		SaveData();
		MessageBox(g_hWnd,L"Ȯ��", L"�޼���", MB_OK);
		return;
	}

	if(GetAsyncKeyState(VK_LEFT))
		m_fScrollX += m_fSpeed;

	if(GetAsyncKeyState(VK_RIGHT))
		m_fScrollX -= m_fSpeed;

}

void CMyEdit::Render(HDC hdc)
{
	MoveToEx(hdc, int(m_tStartPoint.fX + m_fScrollX), (int)m_tStartPoint.fY, NULL);

	for(list<LINE*>::iterator	iter = m_LineList.begin();
		iter != m_LineList.end(); ++iter)
	{
		LineTo(hdc, int((*iter)->tRPoint.fX + m_fScrollX), (int)(*iter)->tRPoint.fY);
	}
}

void CMyEdit::Release(void)
{
	for(list<LINE*>::iterator	iter = m_LineList.begin();
		iter != m_LineList.end(); ++iter)
	{
		::Safe_Delete(*iter);
	}
	m_LineList.clear();
}

void CMyEdit::SaveData(void)
{
	HANDLE		hFile  = NULL;
	DWORD		dwByte = 0;

	hFile = CreateFile(L"../Data/line.dat",		// ������ ����Ǵ� ���
						GENERIC_WRITE,			// ���� ���� ���
						0,						// ���� ��� ���� ��
						NULL,					// ���� ���� ���� ��
						CREATE_ALWAYS,			// ����� ���� ���� ��
						FILE_ATTRIBUTE_NORMAL,	// ������ Ư�� ������ ����(�Ϲ� ���� ��������)			
						NULL);					// ������ �����ϴ� ���ϰ� ������ Ư���� ���� �������� ����(�ʿ� ����)

	for(list<LINE*>::iterator	iter = m_LineList.begin();
		iter != m_LineList.end(); ++iter)
	{
		WriteFile(hFile, (*iter), sizeof(LINE), &dwByte, NULL);
	}

	CloseHandle(hFile);

}