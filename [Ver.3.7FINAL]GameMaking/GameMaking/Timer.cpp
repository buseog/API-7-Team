#include "StdAfx.h"
#include "Timer.h"

CTimer::CTimer(void)
{
}

CTimer::~CTimer(void)
{
}
void CTimer::SetTimer(void)
{
	for (int i = 0; i < 10; ++i)
	{
		RemainTime[i] = i * 1000;
	}
}