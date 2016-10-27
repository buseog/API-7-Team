#pragma once
#include "MainGame.h"

class CStage_2	:
	public CMainGame
{
private:
	list<CObj*>*	m_ObjList[OBJ_END];

public:
	void SetObjList(int _iNum, list<CObj*>* _pObjList);
	int Stage_Clear(void);
public:
	virtual void LoadData(void);
	virtual	void Initialize(void);
	virtual	void Progress(float _fTime);
	virtual	void Render(void);
	virtual	void Release(void);

public:
	CStage_2(void);
	~CStage_2(void);
};
