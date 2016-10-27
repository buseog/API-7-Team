#include "StdAfx.h"
#include "Interface.h"

CInterface::CInterface(void)
{
}

CInterface::~CInterface(void)
{
}

void CInterface::Initialize(void)
{
	m_pMainGame = new CMainGame;
	m_pMainGame->Initialize();
}
void CInterface::Progress(float _fTime)
{
	if(m_pMainGame->GetIntro() != 0)
	{
		m_pMainGame->Intro();
	}
	else
	{
		m_pMainGame->Progress(_fTime);
		m_pMainGame->Render();
	}
}