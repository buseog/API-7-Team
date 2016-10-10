#pragma once

#include "Obj.h"

template<typename T>	
class CAbstractFactory
{
public:
	static CObj*		CreateObj(void)
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		CreateObj(float _fX, float _fY, int _iInput) //ÁÂÇ¥, HP, °ø°Ý·Â
	{
		CObj*		pObj = new T(_iInput);
		pObj->Initialize();
		pObj->SetXY(_fX, _fY);

		return pObj;
	}

public:
	CAbstractFactory(void){}
	~CAbstractFactory(void){}
};
