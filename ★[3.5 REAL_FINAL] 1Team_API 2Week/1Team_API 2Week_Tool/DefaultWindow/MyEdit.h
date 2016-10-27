#pragma once
#include "obj.h"

class CMyEdit :
	public CObj
{
private:
	bool		m_bStart;
	LINEPOINT	m_tStartPoint;
	LINEPOINT	m_tBoxStartPoint;
	list<LINE*>	m_Stage_Line;
	list<LINE*>	m_Stage_Rec;

	list<LINEPOINT*>	m_Monster1List;
	list<LINEPOINT*>	m_Monster2List;
	list<LINEPOINT*>	m_Monster3List;

	int			m_iType;
	float		m_fScrollX;

public:
	void		SaveData(void);
	void LoadData(void);
public:
	CMyEdit(void);
	~CMyEdit(void);

	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

};
