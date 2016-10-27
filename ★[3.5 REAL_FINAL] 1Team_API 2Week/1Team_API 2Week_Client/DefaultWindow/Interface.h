#pragma once
#include "MainGame.h"

class CInterface
{
private:
	CMainGame* m_pMainGame;

public:
	void Initialize(void);
	void Progress(float _fTime);

public:
	CInterface(void);
	~CInterface(void);
};
