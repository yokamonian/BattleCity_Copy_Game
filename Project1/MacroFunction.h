#pragma once
#include "pch.h"

inline void SetWindowSize(int x, int y, int width, int height)
{
	// ������ �۾����� ����
	RECT rc;
	rc.left = 0; rc.top = 0;
	rc.right = width; rc.bottom = height;

	// ���� ������ ũ�� �޾ƿ´�.
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// �̵�
	MoveWindow(g_hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, true);
}

inline RECT GetRectToCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2),
		x + (width / 2), y + (height / 2) };
	return rc;
}
