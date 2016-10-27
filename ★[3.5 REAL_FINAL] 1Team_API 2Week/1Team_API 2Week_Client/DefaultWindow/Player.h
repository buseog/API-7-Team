#pragma once
#include "obj.h"

class CBullet;

class CPlayer :
	public CObj
{
private:
	list<CObj*>*	m_pBulletList;
	list<LINE*>*	m_pLine;
	float			fX;
	float			fY;
	float			m_fDistance;
	float			m_fMaxHp;
	RECT			rc;
	int				m_iRidecount;
	TCHAR			m_szHp[128];

	bool			m_bJump;
	int				m_iWeaponType; //총을 구별하기위함
	float			m_fTime;
	float			m_fOriginY;
	float			m_fOffSetX;

private:
	void	Scroll(void);
	void	KeyInput(float _fTime);
	void	LineCollision(void);
	CObj*   CreateBullet(float _fAngle, int _iType);
public:
	void	SetStageUp(void);
	void	SetJump(bool YN);
	void	SetScrollX(void);
	void	SetOffset(void);
	void	SetLine(list<LINE*>* pLine);
	void	SetBulletList(list<CObj*>* pBulletList);

public:
	virtual void Initialize(void);
	virtual void Progress(float _fTime);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CPlayer(void);
	CPlayer(int _iType);
	~CPlayer(void);

};
