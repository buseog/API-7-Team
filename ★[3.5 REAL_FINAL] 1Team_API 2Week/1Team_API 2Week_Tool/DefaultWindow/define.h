#pragma once

#define PURE = 0

extern HWND g_hWnd;

const int WINCX = 800;
const int WINCY = 600;

typedef struct tagInfo
{
	float fX; 
	float fY;
	float fCX; 
	float fCY;

	tagInfo(void){}
	tagInfo(float _fX, float _fY, float _fCX, float _fCY)
		: fX(_fX), fY(_fY), fCX(_fCX), fCY(_fCY)
	{

	}

}INFO;

template<typename T>
static void Safe_Delete(T& Temp)
{
	if(Temp)
	{
		delete Temp;
		Temp = NULL;
	}
}

static POINT GetMouse(void)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return pt;
}


typedef struct tagLinePoint
{
	float		fX;
	float		fY;

	tagLinePoint(){}
	tagLinePoint(float _fX, float _fY) 
		: fX(_fX), fY(_fY)
	{

	}

}LINEPOINT;

typedef	struct tagLine
{
	LINEPOINT		tLPoint;
	LINEPOINT		tRPoint;

	tagLine(void){}
	tagLine(LINEPOINT	_tLpoint, LINEPOINT _tRpoint)
		: tLPoint(_tLpoint), tRPoint(_tRpoint)
	{

	}
}LINE;