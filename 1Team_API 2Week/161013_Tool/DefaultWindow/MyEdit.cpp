#include "StdAfx.h"
#include "MyEdit.h"



CMyEdit::CMyEdit(void)
	:m_iType(0)
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

	if(GetAsyncKeyState('1'))
	{
		if (m_Stage1[0].size() == 0)
		{
			m_bStart = true;
			m_tStartPoint = tMousePos;
		}
		m_iType = 1;	
	}

	if (GetAsyncKeyState('2'))
	{
		m_iType = 2;
		m_tBoxStartPoint = tMousePos;
		m_bStart = true;
	}
	if (GetAsyncKeyState('A'))
	{
		Safe_Delete(m_Stage1[m_iType - 1].back());
		m_Stage1[m_iType - 1].pop_back();
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_iType == 1)
		{
			if (m_bStart == true)
			{
				m_Stage1[0].push_back(new LINE(m_tStartPoint, tMousePos));
				m_bStart = false;
			}
			else
			{
				m_Stage1[0].push_back(new LINE(m_Stage1[0].back()->tRPoint, tMousePos));
			}
		}
		else if (m_iType == 2)
		{
			m_Stage1[1].push_back(new LINE(m_tBoxStartPoint, tMousePos));
			m_bStart = false;
		}
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
	if (m_Stage1[0].size() != 0)
	{
		MoveToEx(hdc, int(m_tStartPoint.fX + m_fScrollX), (int)m_tStartPoint.fY, NULL);

		for (list<LINE*>::iterator	iter = m_Stage1[0].begin();
			iter != m_Stage1[0].end(); ++iter)
		{
			LineTo(hdc, int((*iter)->tRPoint.fX + m_fScrollX), (int)(*iter)->tRPoint.fY);
		}
	}

	if (m_Stage1[1].size() != 0)
	{
		for (list<LINE*>::iterator	iter = m_Stage1[1].begin();
			iter != m_Stage1[1].end(); ++iter)
		{
			Rectangle(hdc, (*iter)->tLPoint.fX + m_fScrollX, (*iter)->tLPoint.fY, (*iter)->tRPoint.fX + m_fScrollX, (*iter)->tRPoint.fY);
		}
	}
}

void CMyEdit::Release(void)
{
	for (int i = 0; i < 2; ++i)
	{
		for (list<LINE*>::iterator	iter = m_Stage1[i].begin();
			iter != m_Stage1[i].end(); ++iter)
		{
			::Safe_Delete(*iter);
		}
		m_Stage1[i].clear();
	}
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

	for (int i = 0; i < 2; ++i)
	{
		for (list<LINE*>::iterator	iter = m_Stage1[i].begin();
			iter != m_Stage1[i].end(); ++iter)
		{
			WriteFile(hFile, (*iter), sizeof(LINE), &dwByte, NULL);
		}
	}
	CloseHandle(hFile);

}