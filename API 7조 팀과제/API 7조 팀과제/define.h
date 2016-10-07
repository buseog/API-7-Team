#pragma once

#define PURE = 0

extern HWND g_hWnd;
const int WINCX = 800;
const int WINCY = 600;

template<typename T>
static void SAFE_DELETE(T& pTemp)
{
	if (pTemp)
	{
		delete pTemp;
		pTemp = NULL;
	}
}

