#pragma once
#include "obj.h"

class CBullet :
	public CObj
{
private:
	int		m_iStan;
	int		m_iType;

public:
	void Initialize(void);
	void Progress(float _Time);		
	void Render(HDC hdc);	
	void Release(void);	

public:
	void NomalType(void);
	void TargetType(float _Time);
	void ChargeType(float _Time);
	void BuckType(void);
	void UltiType(float _Time);
public:
	CBullet(void);
	CBullet(int _iInput);
	~CBullet(void);
};
