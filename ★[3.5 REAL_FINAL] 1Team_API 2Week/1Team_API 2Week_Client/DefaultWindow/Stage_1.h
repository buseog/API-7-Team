#pragma once
#include "MainGame.h"

class CStage_1	:
	public CMainGame
{
private:
	list<CObj*>*	m_ObjList[OBJ_END];//0.플레이어 1. 불렛 2. 아이템 3. 몬스터 4. 보스 5. 박스
	RECT			rc;

public:
	void SetObjList(int _iNum, list<CObj*>* _pObjList); // 메인게임이 가진 OBJ들을 동기화.
	int Stage_Clear(void);

public:
	virtual void LoadData(void);
	virtual	void Initialize(void);
	virtual	void Progress(float _fTime);
	virtual	void Render(void);
	virtual	void Release(void);

public:
	CStage_1(void);
	~CStage_1(void);
};
