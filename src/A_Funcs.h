#pragma once

void			adminMainThread(void);
void			OnCloseDialog(void *pDialog);
void			D3DColorToStringColor(D3DCOLOR dwColor, char* szOutColor);
bool			stringToD3DColor(const char* szStrColor, D3DCOLOR* dwOutColor);
LRESULT			CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT			CALLBACK LLKeyProc(int nCode, WPARAM wParam, LPARAM lParam);
void			SravnenieIP(const std::string& reg_ip, const std::string& current_ip);
void			addAdminCommand(char *name, CMDPROC function);
void            string2Keycombo(const std::string &str, keycombo &ret);
std::string     keycombo2String(const keycombo &keycombo);
void            adminLog(FILE *fileLog, const char *fmt, ...);
void            stringSplit(std::string const &source, std::string const &delimiter, std::vector <std::string> &out);