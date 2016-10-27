#pragma once
#include "Obj.h"
#include "define.h"
#include "Timer.h"

class CStage_1;
class CStage_2;
class CObj;
class CMainGame
{
protected:
	HDC			m_hdc;
	list<CObj*>		m_ObjList[OBJ_END]; //0.플레이어 1. 불렛 2. 아이템 3. 몬스터 4. 보스 5. 박스
	CTimer			m_CTimer;
	list<LINE*>		m_LineList;
	list<LINE*>		m_RecList;
	list<LINEPOINT*>	m_MonList;
private:
	int			m_iIntro;
	int			m_iStage;
	CStage_1*	m_CStage1;
	CStage_2*	m_CStage2;
public:
	void Intro(void);
	int GetIntro(void);
public:
	virtual void LoadData(void);
	virtual	void Initialize(void);
	virtual	void Progress(float _fTime);
	virtual	void Render(void);
	virtual	void Release(void);

public:
	CMainGame(void);
	virtual ~CMainGame(void);
};
