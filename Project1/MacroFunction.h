#pragma once
#include "pch.h"

inline void SetWindowSize(int x, int y, int width, int height)
{
	// 윈도우 작업영역 지정
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = width; rc.bottom = height;

	// 실제 윈도우 크기 받아온다.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 이동
	MoveWindow(g_hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, true);
}

inline RECT GetRectToCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2),
		x + (width / 2), y + (height / 2) };
	return rc;
}
