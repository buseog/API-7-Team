#pragma once

#include "define.h"
#include "MainGame.h"

class CInterface
{
private:
	CMainGame*		m_pMainGame;
	HDC				m_hdc;

public:
	void Initialize(void);
	void Progress(float _Time);
	void Release(void);	

public:
	CInterface(void);
	~CInterface(void);
};
