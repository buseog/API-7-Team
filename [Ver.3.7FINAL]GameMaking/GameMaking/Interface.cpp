#include "StdAfx.h"
#include "Interface.h"

CInterface::CInterface(void)
{
}

CInterface::~CInterface(void)
{
	Release();
}

void CInterface::Initialize(void)	
{
	m_pMainGame = new CMainGame;
	m_pMainGame->Initialize();
}

void CInterface::Progress(float _Time)
{
	if (m_pMainGame->GetIntro() > 0)
	{
		m_pMainGame->Intro();
	}
	else
	{
		m_pMainGame->Progress(_Time);
		m_pMainGame->Render();
	}
}

void CInterface::Release(void)
{
	Safe_Delete(m_pMainGame);
}