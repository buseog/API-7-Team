#pragma once

#include "define.h"

class CInterface
{
private:

public:
	void Initialize(void);
	void Progress(void);
	void Render(void);
	void Release(void);

public:
	CInterface(void);
	~CInterface(void);
};
