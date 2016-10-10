#pragma once
#include "maingame.h"

class CStage3 :
	public CMainGame
{
private:
	int		iWave;
	list<CObj*>*		m_ListObj[OBJ_END];

public:
	virtual void Initialize(void);
	virtual void Progress(float _Time);
	virtual void Render(void);
	virtual void Release(void);

public:
	void SetListObj(int _iNum, list<CObj*>* _pListObj);
	int Clear(void);

public:
	CStage3(void);
	~CStage3(void);
};
