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

	static CObj*		CreateObj(float _fX, float _fY)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->SetPos(_fX, _fY);

		return pObj;
	}

public:
	CAbstractFactory(void){}
	~CAbstractFactory(void){}
};
