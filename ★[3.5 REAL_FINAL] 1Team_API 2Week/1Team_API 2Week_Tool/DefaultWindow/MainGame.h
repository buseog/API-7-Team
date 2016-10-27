#pragma once

#include "define.h"

class CObj;
class CMainGame
{
private:
	HDC			m_hdc;
	
	CObj*		m_pMyEdit;

public:
	void Initialize(void);
	void Progress(void);
	void Render(void);
	void Release(void);

public:
	CMainGame(void);
	~CMainGame(void);
};
