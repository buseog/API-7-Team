#pragma once
#include "obj.h"

class CMonster :
	public CObj
{
private:
	list<CObj*>*	m_pMBulletList;//몬스터 불렛 리스트
	//플레이어 불렛 리스트 추가
	//아이템 리스트 추가
	CObj*			m_pPlayer;// 몬스터가플레이어의 위치를 알아야해서 플레이어 하나 만듬
public:
	void SetMBulletList(list<CObj*>* _pMBulletList);//몬스터블렛리스트셋함수
	void SetPlayer(CObj* _pPlayer);//플레이어 셋함수(메인게임에서셋해줌)
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
