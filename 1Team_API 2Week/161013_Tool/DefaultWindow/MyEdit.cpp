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

	hFile = CreateFile(L"../Data/line.dat",		// 파일이 저장되는 경로
						GENERIC_WRITE,			// 쓰기 전용 모드
						0,						// 공유 모드 설정 값
						NULL,					// 보안 상태 설정 값
						CREATE_ALWAYS,			// 만드는 상태 지정 값
						FILE_ATTRIBUTE_NORMAL,	// 파일의 특정 정보를 삽입(일반 파일 지정상태)			
						NULL);					// 기존에 존재하는 파일과 동등한 특성을 가진 새파일을 생성(필요 없음)

	for(list<LINE*>::iterator	iter = m_LineList.begin();
		iter != m_LineList.end(); ++iter)
	{
		WriteFile(hFile, (*iter), sizeof(LINE), &dwByte, NULL);
	}

	CloseHandle(hFile);

}