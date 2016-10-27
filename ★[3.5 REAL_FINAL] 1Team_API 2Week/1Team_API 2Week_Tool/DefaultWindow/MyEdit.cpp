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
	LoadData();
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
		if (m_Stage_Line.size() == 0)
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

	if (GetAsyncKeyState('3') & 0x8000)
	{
		m_iType = 3;
		m_Monster1List.push_back(new LINEPOINT(tMousePos.fX,tMousePos.fY));
	}
	
	if (GetAsyncKeyState('4') & 0x8000)
	{
		m_iType = 4;
		m_Monster2List.push_back(new LINEPOINT(tMousePos.fX,tMousePos.fY));
	}

	if (GetAsyncKeyState('5') & 0x8000)
	{
		m_iType = 5;
		m_Monster3List.push_back(new LINEPOINT(tMousePos.fX,tMousePos.fY));
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		switch (m_iType)
		{
		case 1:
			if (m_Stage_Line.size() != 0)
			{
				Safe_Delete(m_Stage_Line.back());
				m_Stage_Line.pop_back();
			}
			break;
		case 2:
			if (m_Stage_Rec.size() != 0)
			{
				Safe_Delete(m_Stage_Rec.back());
				m_Stage_Rec.pop_back();
			}
			break;
		case 3:
			if (m_Monster1List.size() != 0)
			{
				Safe_Delete(m_Monster1List.back());
				m_Monster1List.pop_back();
			}
			break;
		case 4:
			if (m_Monster2List.size() != 0)
			{
				Safe_Delete(m_Monster2List.back());
				m_Monster2List.pop_back();
			}
			break;
		case 5:
			if (m_Monster3List.size() != 0)
			{
				Safe_Delete(m_Monster3List.back());
				m_Monster3List.pop_back();
			}
			break;
		}
		
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_iType == 1)
		{
			if (m_bStart == true)
			{
				m_Stage_Line.push_back(new LINE(m_tStartPoint, tMousePos));
				m_bStart = false;
			}
			else
			{
				m_Stage_Line.push_back(new LINE(m_Stage_Line.back()->tRPoint, tMousePos));
			}
		}
		else if (m_iType == 2)
		{
			m_Stage_Rec.push_back(new LINE(m_tBoxStartPoint, tMousePos));
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

	int ab = GetMouse().x - m_fScrollX;
	TCHAR a[10];
	wsprintf(a, L"%d",ab );
	TCHAR b[10];
	wsprintf(b, L"%d", GetMouse().y);
	TextOut(hdc, 50, 50, a, sizeof(int));
	TextOut(hdc, 50, 70, b, sizeof(int));

	if (m_Stage_Line.size() != 0)
	{
		MoveToEx(hdc, int(m_tStartPoint.fX + m_fScrollX), (int)m_tStartPoint.fY, NULL);

		for (list<LINE*>::iterator	iter = m_Stage_Line.begin();
			iter != m_Stage_Line.end(); ++iter)
		{
			LineTo(hdc, int((*iter)->tRPoint.fX + m_fScrollX), (int)(*iter)->tRPoint.fY);
		}
	}

	if (m_Stage_Rec.size() != 0)
	{
		for (list<LINE*>::iterator	iter = m_Stage_Rec.begin();
			iter != m_Stage_Rec.end(); ++iter)
		{
			Rectangle(hdc, (*iter)->tLPoint.fX + m_fScrollX, (*iter)->tLPoint.fY, (*iter)->tRPoint.fX + m_fScrollX, (*iter)->tRPoint.fY);
		}
	}

	if (m_Monster1List.size() != 0)
	{
		for (list<LINEPOINT*>::iterator	iter = m_Monster1List.begin();
			iter != m_Monster1List.end(); ++iter)
		{
			Rectangle(hdc, (*iter)->fX - 3+ m_fScrollX, (*iter)->fY - 3, (*iter)->fX + 3 + m_fScrollX, (*iter)->fY + 3);
		}
	}

	if (m_Monster2List.size() != 0)
	{
		for (list<LINEPOINT*>::iterator	iter = m_Monster2List.begin();
			iter != m_Monster2List.end(); ++iter)
		{
			Rectangle(hdc, (*iter)->fX - 5+ m_fScrollX, (*iter)->fY - 5, (*iter)->fX + 5 + m_fScrollX, (*iter)->fY + 5);
		}
	}

	if (m_Monster3List.size() != 0)
	{
		for (list<LINEPOINT*>::iterator	iter = m_Monster3List.begin();
			iter != m_Monster3List.end(); ++iter)
		{
			Rectangle(hdc, (*iter)->fX - 7+ m_fScrollX, (*iter)->fY - 7, (*iter)->fX + 7 + m_fScrollX, (*iter)->fY + 7);
		}
	}
}

void CMyEdit::Release(void)
{

	for (list<LINE*>::iterator	iter = m_Stage_Line.begin();
		iter != m_Stage_Line.end(); ++iter)
	{
		::Safe_Delete(*iter);
	}
	m_Stage_Line.clear();
	for (list<LINE*>::iterator	iter = m_Stage_Rec.begin();
		iter != m_Stage_Rec.end(); ++iter)
	{
		::Safe_Delete(*iter);
	}
	m_Stage_Rec.clear();

}

void CMyEdit::SaveData(void)
{
	HANDLE		hFile  = NULL;
	DWORD		dwByte = 0;

	hFile = CreateFile(L"../Data/Line1.dat",		// 파일이 저장되는 경로
						GENERIC_WRITE,			// 쓰기 전용 모드
						0,						// 공유 모드 설정 값
						NULL,					// 보안 상태 설정 값
						CREATE_ALWAYS,			// 만드는 상태 지정 값
						FILE_ATTRIBUTE_NORMAL,	// 파일의 특정 정보를 삽입(일반 파일 지정상태)			
						NULL);					// 기존에 존재하는 파일과 동등한 특성을 가진 새파일을 생성(필요 없음)


	for (list<LINE*>::iterator	iter =m_Stage_Line.begin();
		iter != m_Stage_Line.end(); ++iter)
	{
		WriteFile(hFile, (*iter), sizeof(LINE), &dwByte, NULL);
	}

	CloseHandle(hFile);

	hFile = CreateFile(L"../Data/Rec1.dat",		// 파일이 저장되는 경로
		GENERIC_WRITE,			// 쓰기 전용 모드
		0,						// 공유 모드 설정 값
		NULL,					// 보안 상태 설정 값
		CREATE_ALWAYS,			// 만드는 상태 지정 값
		FILE_ATTRIBUTE_NORMAL,	// 파일의 특정 정보를 삽입(일반 파일 지정상태)			
		NULL);	

	for (list<LINE*>::iterator	iter =m_Stage_Rec.begin();
		iter != m_Stage_Rec.end(); ++iter)
	{
		WriteFile(hFile, (*iter), sizeof(LINE), &dwByte, NULL);
	}

	CloseHandle(hFile);

	//몬스터 저장
	hFile = CreateFile(L"../Data/Mon11.dat",		// 파일이 저장되는 경로
						GENERIC_WRITE,			// 쓰기 전용 모드
						0,						// 공유 모드 설정 값
						NULL,					// 보안 상태 설정 값
						CREATE_ALWAYS,			// 만드는 상태 지정 값
						FILE_ATTRIBUTE_NORMAL,	// 파일의 특정 정보를 삽입(일반 파일 지정상태)			
						NULL);					// 기존에 존재하는 파일과 동등한 특성을 가진 새파일을 생성(필요 없음)


	for (list<LINEPOINT*>::iterator	iter = m_Monster1List.begin();
		iter != m_Monster1List.end(); ++iter)
	{
		WriteFile(hFile, (*iter), sizeof(LINEPOINT), &dwByte, NULL);
	}

	CloseHandle(hFile);

	//몬스터 저장
	hFile = CreateFile(L"../Data/Mon12.dat",		// 파일이 저장되는 경로
						GENERIC_WRITE,			// 쓰기 전용 모드
						0,						// 공유 모드 설정 값
						NULL,					// 보안 상태 설정 값
						CREATE_ALWAYS,			// 만드는 상태 지정 값
						FILE_ATTRIBUTE_NORMAL,	// 파일의 특정 정보를 삽입(일반 파일 지정상태)			
						NULL);					// 기존에 존재하는 파일과 동등한 특성을 가진 새파일을 생성(필요 없음)


	for (list<LINEPOINT*>::iterator	iter = m_Monster2List.begin();
		iter != m_Monster2List.end(); ++iter)
	{
		WriteFile(hFile, (*iter), sizeof(LINEPOINT), &dwByte, NULL);
	}

	CloseHandle(hFile);

	//몬스터 저장
	hFile = CreateFile(L"../Data/Mon11.dat",		// 파일이 저장되는 경로
						GENERIC_WRITE,			// 쓰기 전용 모드
						0,						// 공유 모드 설정 값
						NULL,					// 보안 상태 설정 값
						CREATE_ALWAYS,			// 만드는 상태 지정 값
						FILE_ATTRIBUTE_NORMAL,	// 파일의 특정 정보를 삽입(일반 파일 지정상태)			
						NULL);					// 기존에 존재하는 파일과 동등한 특성을 가진 새파일을 생성(필요 없음)


	for (list<LINEPOINT*>::iterator	iter = m_Monster3List.begin();
		iter != m_Monster3List.end(); ++iter)
	{
		WriteFile(hFile, (*iter), sizeof(LINEPOINT), &dwByte, NULL);
	}

	CloseHandle(hFile);
}


void CMyEdit::LoadData(void)
{
	HANDLE		hFile = NULL;
	DWORD		dwByte = 0;

	hFile = CreateFile(L"../Data/Line2.dat", 
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
		m_Stage_Line.push_back(pLine);
	}

	CloseHandle(hFile);

	hFile = CreateFile(L"../Data/Rec2.dat",
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

		m_Stage_Rec.push_back(pLine);
	}

	CloseHandle(hFile);
	//몬스터1
	hFile = CreateFile(L"../Data/Mon21.dat",
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	while(true)
	{
		LINEPOINT*		pLinePOINT = new LINEPOINT;

		ReadFile(hFile, pLinePOINT, sizeof(LINEPOINT), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pLinePOINT);
			break;
		}

		m_Monster1List.push_back(pLinePOINT);
	}

	CloseHandle(hFile);

	hFile = CreateFile(L"../Data/Mon22.dat",
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	while(true)
	{
		LINEPOINT*		pLinePOINT = new LINEPOINT;

		ReadFile(hFile, pLinePOINT, sizeof(LINEPOINT), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pLinePOINT);
			break;
		}

		m_Monster2List.push_back(pLinePOINT);
	}

	CloseHandle(hFile);

	hFile = CreateFile(L"../Data/Mon23.dat",
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	while(true)
	{
		LINEPOINT*		pLinePOINT = new LINEPOINT;

		ReadFile(hFile, pLinePOINT, sizeof(LINEPOINT), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pLinePOINT);
			break;
		}

		m_Monster3List.push_back(pLinePOINT);
	}

	CloseHandle(hFile);
}