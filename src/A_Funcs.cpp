#include "main.h"

const char *szFracktionName[] =
{
	"LSPD",
	"FBI",
	"LVa",
	"MOH",
	"LCN",
	"Yakuza",
	"Mayor",
	"RM",
	"SFn",
	"LSn",
	"Instrustors",
	"Rifa",
	"Grove",
	"Ballas",
	"Vagos",
	"Aztec",
	"SFPD",
	"LVPD",
	"SFa",
	"None",
	"LVn",
	"Hell Angel's MC",
	"Mongols MC",
	"Pagans MC",
	"Outlaws MC",
	"Son's Of Silence MC",
	"Warlocks MC",
	"Highwayman MC",
	"Bandidos MC",
	"FreeSouls MC",
	"Vagos MC"
};

/*char* getfractionname(int fractionId)
	{
		switch (fractionId) { case 1: return "LSPD"; case 2: return "FBI"; case 3: return "LVa"; 
		case 4: return "MOH"; case 5: return "LCN"; case 6: return "Yakuza"; case 7: return "Mayor"; 
		case 8: return "RM"; case 9: return "SFn"; case 10: return "LSn"; case 11: return "Instrustors"; 
		case 12: return "Rifa"; case 13: return "Grove"; case 14: return "Ballas"; case 15: return "Vagos"; 
		case 16: return "Aztec"; case 17: return "SFPD"; case 18: return "LVPD"; case 19: return "SFa"; 
		case 21: return "LVn"; case 22: return "Hell Angel's MC"; case 23: return "Mongols MC"; 
		case 24: return "Pagans MC"; case 25: return "Outlaws MC"; case 26: return "Son's Of Silence MC"; 
		case 27: return "Warlocks MC"; case 28: return "Highwayman MC"; case 29: return "Bandidos MC"; 
		case 30: return "FreeSouls MC"; case 31: return "Vagos MC"; }
	}
	*/
void OnCloseDialog(void *pDialog)
{
	stDialogInfo Dialog = *(stDialogInfo*)pDialog;
	switch (Dialog.iType)
	{
	case DialogStyle::DIALOG_STYLE_LIST:
	{
		int iSelectItem = *(int*)(uint32_t(Dialog.pList) + 0x147);
		switch (Dialog.DialogID)
		{
		case 2:
		{
			if (A_Set.usSetLeaderID > 999)
			{
				return;
			}

			if (iSelectItem < 20)
				A_Set.byteFrackID = iSelectItem;
			else
				A_Set.byteFrackID = iSelectItem + 1;

			if (A_Set.byteFrackID != 0)
				ShowLocalSampDialog(3, DIALOG_STYLE_MSGBOX, "Подтверждение", (char *)std::string("Вы уверены что хотите назначить " + std::string(getPlayerName(A_Set.usSetLeaderID)) + " на лидерство " + szFracktionName[A_Set.byteFrackID - 1]/*std::string(getfractionname(byteFrackID))*/).c_str(), "Назначить", "Закрыть");
			else
				ShowLocalSampDialog(3, DIALOG_STYLE_MSGBOX, "Подтверждение", (char *)std::string("Вы уверены что хотите cнять " + std::string(getPlayerName(A_Set.usSetLeaderID)) + " с лидерства").c_str(), "Назначить", "Закрыть");
			break;
		}
		}
		break;
	}

	case DialogStyle::DIALOG_STYLE_INPUT:
	case DialogStyle::DIALOG_STYLE_PASSWORD:
	case DialogStyle::DIALOG_STYLE_MSGBOX:
	{
		switch (Dialog.DialogID)
		{
		case 3:
			say("/makeleader %hd %hhd", A_Set.usSetLeaderID, A_Set.byteFrackID);
			break;
		}
		break;
	}
	}
}

bool stringToD3DColor(const char* szStrColor, D3DCOLOR* dwOutColor)
{
	int len = strlen(szStrColor);
	if (len != 6 && len != 8)
		return false;

	*dwOutColor = 0;

	if (len == 6)
		*dwOutColor = 0xFF << 24;

	len -= 1;

	for (int i = 0; i <= len; i++)
	{
		if (szStrColor[i] < '0' || szStrColor[i] > '9' && szStrColor[i]<'A' || szStrColor[i]>'Z')
			return false;

		byte temp = 0;
		if (szStrColor[i] > '9')
			temp = szStrColor[i] - 'A' + 10;
		else
			temp = szStrColor[i] - '0';

		*dwOutColor |= (temp << ((len - i) * 4));
	}
}

void D3DColorToStringColor(D3DCOLOR dwColor, char *szOutColor)
{
	sprintf(szOutColor, "{%06X}", dwColor & 0x00FFFFFF/*(dwColor << 8) >> 8*/);
}

POINT CursorPos()
{
	POINT CurPos;
	GetCursorPos(&CurPos);
	if (pPresentParam.Windowed)
	{
		RECT *pos = new RECT();
		GetWindowRect(pPresentParam.hDeviceWindow, pos);
		CurPos.x -= (8 + pos->left);
		CurPos.y -= (30 + pos->top);
		delete pos;
	}
	return CurPos;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (g_SAMP != nullptr)
	{
		switch (uMsg)
		{
			//case WM_KEYUP:
			{
				//char *key = key_name(wParam);//code key // не определяет shift/alt/ctrl (другие коды клавишь)
				//addMessageToChatWindow("Key: %s, Code: 0x%X | lParam: 0x%X", key, wParam, lParam);
			break;
			}
		}
	}
	return CallWindowProcA(WNDPROC(lOldWndProc), hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK LLKeyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (GetForegroundWindow() == *(HWND*)0xC97C1C)
	{
		if (g_SAMP != nullptr)
		{
			if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
			{
				return -1;
			}
			else
			if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
			{
				if (nCode == HC_ACTION)
				{
					DWORD vk = ((LPKBDLLHOOKSTRUCT)lParam)->vkCode;
					
					char *key = key_name(vk);
					addMessageToChatWindow("[HOOK] Key: %s (0x%X)", key, vk);

					return 0;
				}
			}
		}
	}
	///UnhookWindowsHookEx(hook);
	///hook = 0;
	return CallNextHookEx(hhKeyKook, nCode, wParam, lParam);
}