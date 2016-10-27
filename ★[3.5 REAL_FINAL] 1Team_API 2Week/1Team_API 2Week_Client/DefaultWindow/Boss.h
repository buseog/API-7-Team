#pragma once
#include "obj.h"

class CBoss :
	public CObj
{
private:
	float			m_fSpeed;
	list<CObj*>*	m_pMBulletList;
	float			m_fAngle;
public:
	virtual void Initialize(void);
	virtual void Progress(float _fTime);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	void	SetMBulletList	(list<CObj*>* _pMBulletList);//���ͺ�����Ʈ���Լ�
public:
	CBoss(void);
	CBoss(int _iType);
	~CBoss(void);
};
