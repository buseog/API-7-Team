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
		MessageBox(g_hWnd,L"확인", L"메세지", MB_OK);
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

	hFile = CreateFile(L"../Data/line.dat",		// 파일이 저장되는 경로
						GENERIC_WRITE,			// 쓰기 전용 모드
						0,						// 공유 모드 설정 값
						NULL,					// 보안 상태 설정 값
						CREATE_ALWAYS,			// 만드는 상태 지정 값
						FILE_ATTRIBUTE_NORMAL,	// 파일의 특정 정보를 삽입(일반 파일 지정상태)			
						NULL);					// 기존에 존재하는 파일과 동등한 특성을 가진 새파일을 생성(필요 없음)

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