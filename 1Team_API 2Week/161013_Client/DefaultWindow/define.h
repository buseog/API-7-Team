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

typedef struct tagStat
{
	float fHp;
	float fAttack;
	float fSpeed;

	tagStat(void){}
	tagStat(float _fHp, float _fAttack, float _fSpeed)
		: fHp(_fHp), fAttack(_fAttack), fSpeed(_fSpeed)
	{

	}

}STAT;

template<typename T>
static void Safe_Delete(T& Temp)
{
	if(Temp)
	{
		delete Temp;
		Temp = NULL;
	}
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

enum OBJ_TYPE
{
	OBJ_PLAYER,
	OBJ_BULLET,
	OBJ_ITEM,
	OBJ_MONSTER,
	OBJ_BOSS,
	OBJ_BOX,
	OBJ_END
};

enum PLAYER_TYPE
{
	PLAYER_HUMAN,
	PLAYER_TANK
};

enum BULLET_TYPE
{
	BULLET_NORMAL
};

enum ITEM_TYPE
{
	ITEM_ATTACK,
	ITEM_RECOVERY
};

enum MONSTER_TYPE
{
	MONSTER_1,
	MONSTER_2,
	MONSTER_3
};

enum BOSS_TYPE
{
	BOSS_1,
	BOSS_2
};

enum BOX_TYPE
{
	BOX_NORMAL
};

enum STAGE_TYPE
{
	STAGE_1,
	STAGE_2
};