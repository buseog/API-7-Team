#pragma once

#define PURE = 0

template<typename T>
static void Safe_Delete(T& Temp)
{
	if(Temp)
	{
		delete Temp;
		Temp = NULL;
	}
}

extern HWND g_hWnd;

const int WINCX = 800;
const int WINCY = 600;

typedef struct tagInfo
{
	float		fX;
	float		fY;
	float		fCX;
	float		fCY;

	tagInfo(){}
	tagInfo(float _fX, float _fY, float _fCX, float _fCY)
		: fX(_fX), fY(_fY), fCX(_fCX), fCY(_fCY)
	{

	}

}INFO;

typedef struct tagSTAT
{
	float fHp;
	float fFullHp;
	float fAttack;
	float fSpeed;
	bool  Destroy;
	int iKey;

	tagSTAT(){}
	tagSTAT(float _fHp, float _fFullHp, float _fAttack, float _fSpeed)
		: fHp(_fHp), fFullHp(_fFullHp), fAttack(_fAttack), fSpeed(_fSpeed)
	{
		Destroy = 0;
	}

}STAT;

enum OBJID
{
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_BULLET,
	OBJ_MONBULLET,
	OBJ_ITEM,
	OBJ_END
};