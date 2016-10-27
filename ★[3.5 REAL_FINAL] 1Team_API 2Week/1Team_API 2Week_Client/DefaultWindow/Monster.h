#pragma once
#include "obj.h"

class CMonster :
	public CObj
{
private:
	list<CObj*>*	m_pMBulletList;//���� �ҷ� ����Ʈ
	//�÷��̾� �ҷ� ����Ʈ �߰�
	//������ ����Ʈ �߰�
	CObj*			m_pPlayer;// ���Ͱ��÷��̾��� ��ġ�� �˾ƾ��ؼ� �÷��̾� �ϳ� ����
public:
	void SetMBulletList(list<CObj*>* _pMBulletList);//���ͺ�����Ʈ���Լ�
	void SetPlayer(CObj* _pPlayer);//�÷��̾� ���Լ�(���ΰ��ӿ���������)
public:
	virtual void Initialize(void);
	virtual void Progress(float _fTime);
	virtual void Render(HDC hdc);
	virtual void Release(void);
public:
	CMonster(void);
	CMonster(int _iType);
	~CMonster(void);
};
