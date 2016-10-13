#pragma once
#include "obj.h"

class CBullet;

class CPlayer :
	public CObj
{
private:
	list<CObj*>*	m_pBulletList;
	list<LINE*>*	m_pLine;

	bool			m_bJump;
	float			m_fTime;
	float			m_fOriginY;
	float			m_fOffSetX;
	float			m_fAngle;	

private:
	void	Scroll(void);
	void	KeyInput(void);
	void	LineCollision(void);

public:
	void	SetLine(list<LINE*>* pLine);
	void	SetBulletList(list<CObj*>* pBulletList);

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CPlayer(void);
	CPlayer(int _iType);
	~CPlayer(void);

};
