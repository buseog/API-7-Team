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
		m_fRemainTime[i] = 0 * 1000;
	}
}