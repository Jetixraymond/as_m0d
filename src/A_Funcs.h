#pragma once

void			OnCloseDialog(void *pDialog);
void			D3DColorToStringColor(D3DCOLOR dwColor, char* szOutColor);
bool			stringToD3DColor(const char* szStrColor, D3DCOLOR* dwOutColor);
LRESULT			CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT			CALLBACK LLKeyProc(int nCode, WPARAM wParam, LPARAM lParam);