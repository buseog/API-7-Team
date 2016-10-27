#pragma once

#include "Obj.h"

template<typename T>
class CObjFactory
{
public:
	static CObj* CreateObj(void)
	{
		CObj* pObj = new T;

		pObj->Initialize();

		return pObj;
	}
	
	static CObj* CreateObj(float _fX, float _fY, int _iType)
	{
		CObj* pObj = new T(_iType);

		pObj->Initialize();
		pObj->SetPos(_fX, _fY);
		return pObj;
	}
	static CObj* CreateObj(float _fX, float _fY, int _iType, float _fAngle)
	{
		CObj* pObj = new T(_iType);

		pObj->Initialize();
		pObj->SetAngle(_fAngle);
		pObj->SetPos(_fX, _fY);
		return pObj;
	}

public:
	CObjFactory(void){	}
	~CObjFactory(void){	}
};
