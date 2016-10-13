#pragma once
#include "MainGame.h"

class CStage_1	:
	public CMainGame
{
private:
	list<CObj*>*	m_ObjList[OBJ_END];//0.�÷��̾� 1. �ҷ� 2. ������ 3. ���� 4. ���� 5. �ڽ�
	list<LINE*>*		m_LineList;
public:
	void SetObjList(int _iNum, list<CObj*>* _pObjList); // ���ΰ����� ���� OBJ���� ����ȭ.
	void SetLineList(list<LINE*>* _pLineList);
	int Stage_Clear(void);

public:
	virtual	void Initialize(void);
	virtual	void Progress(float _fTime);
	virtual	void Render(void);
	virtual	void Release(void);

public:
	CStage_1(void);
	~CStage_1(void);
};
