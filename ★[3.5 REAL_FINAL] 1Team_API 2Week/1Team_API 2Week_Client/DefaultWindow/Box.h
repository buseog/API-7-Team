#pragma once
#include "obj.h"

class CBox :
	public CObj
{
public:
	void SetPoint(float _fleft, float _ftop, float _fright, float _fbottom);
	RECT GetBox(void);
public:
	virtual void Initialize(void);
	virtual void Progress(float _fTime);
	virtual void Render(HDC hdc);
	virtual void Release(void);	
public:
	CBox(void);
	CBox(int _iType);
	~CBox(void);
};
