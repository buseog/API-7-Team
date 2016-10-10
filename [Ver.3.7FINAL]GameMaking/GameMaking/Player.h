#pragma once
#include "obj.h"

class CPlayer :
	public CObj
{
private:
	int		iStan;
	int		m_iType;
	list<CObj*>*		m_pBullet;
	list<CObj*>*		m_pItem;

private:
	void	KeyInput(void);

public:
	void	SetBulletList(list<CObj*>*	pBullet);
	void	SetItemList(list<CObj*>*	pItem);
	int		GetBulletType(void);
public:
	void	Initialize(void);
	void	Progress(float _Time);		
	void	Render(HDC hdc);	
	void	Release(void);

public:
	CPlayer(void);
	CPlayer(int _iInput);
	~CPlayer(void);
};
