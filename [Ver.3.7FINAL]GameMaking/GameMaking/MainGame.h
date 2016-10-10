#pragma once

#include "define.h"
#include "Timer.h"
#include "Monster.h"
#include "Item.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "Obj.h"

class CStage1;
class CStage2;
class CStage3;
class CObj;

class CMainGame
{
protected:
	CTimer			m_Timer;
	HDC				m_hdc;
	CObj*			m_pPlayer;
	CObj*			m_pItem;
	list<CObj*>		m_ListObj[OBJ_END];	// [0]플레이어 [1]몬스터 [2]미사일 [3]몹미사일 [4] 아이템
	int				m_iIntro;

private:
	int				m_Stage;
	CStage1*		Stage1;
	CStage2*		Stage2;
	CStage3*		Stage3;	

public:
	void	SetPlayer(CObj* _pPlayer);
	void	SetItem(CObj*	_pItem);
	void	TextRender(HDC hdc);
	void	StatRender(HDC hdc);
	void	Intro(void);
	int		GetIntro(void);

public:
	virtual void Initialize(void);
	virtual void Progress(float _Time);
	virtual void Render(void);
	virtual void Release(void);

public:
	CMainGame(void);
	virtual ~CMainGame(void);
};
