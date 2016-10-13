#pragma once
#include "Obj.h"
#include "define.h"

class CStage_1;
class CStage_2;
class CObj;
class CMainGame
{
protected:
	HDC			m_hdc;
	list<CObj*>		m_ObjList[OBJ_END]; //0.�÷��̾� 1. �ҷ� 2. ������ 3. ���� 4. ���� 5. �ڽ�
	list<LINE*>		m_LineList;

private:
	int			m_iStage;
	CStage_1*	m_CStage1;
	CStage_2*	m_CStage2;

private:
	void		LoadData(void);

public:
	virtual	void Initialize(void);
	virtual	void Progress(float _fTime);
	virtual	void Render(void);
	virtual	void Release(void);

public:
	CMainGame(void);
	virtual ~CMainGame(void);
};
