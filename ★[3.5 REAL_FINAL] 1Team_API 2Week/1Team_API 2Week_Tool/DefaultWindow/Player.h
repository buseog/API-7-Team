#pragma once
#include "obj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer(void);
	~CPlayer(void);

private:
	void	KeyInput(void);

public:
	virtual void Initialize(void);
	virtual void Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

};
