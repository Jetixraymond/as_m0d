#include "main.h"

#include <wininet.h>
#pragma comment ( lib, "Wininet.lib" )

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
		if (szStrColor[i] < '0' || (szStrColor[i] > '9' && szStrColor[i] < 'A') || szStrColor[i]>'Z')
			return false;

		byte temp = 0;
		if (szStrColor[i] > '9')
			temp = szStrColor[i] - 'A' + 10;
		else
			temp = szStrColor[i] - '0';

		*dwOutColor |= (temp << ((len - i) * 4));
	}
	return true;
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

float GeoDistance(float *start, float *end)
{
	start[0] *= M_PI / 180;
	start[1] *= M_PI / 180;
	end[0] *= M_PI / 180;
	end[1] *= M_PI / 180;
	float y, x, del = start[1] - end[1];
	y = sqrt(pow(cos(end[0])*sin(del), 2) + pow(cos(start[0])*sin(end[0]) - sin(start[0])*cos(end[0])*cos(del), 2));
	x = sin(start[0])*sin(end[0]) + cos(start[0])*cos(end[0])*cos(del);
	return atan2(y, x) * 6372.795;//km
}

//LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//	if (g_SAMP != nullptr)
//	{
//		switch (uMsg)
//		{
//			//case WM_KEYUP:
//			{
//				//char *key = key_name(wParam);//code key // не определяет shift/alt/ctrl (другие коды клавишь)
//				//addMessageToChatWindow("Key: %s, Code: 0x%X | lParam: 0x%X", key, wParam, lParam);
//			break;
//			}
//		}
//	}
//	return CallWindowProcA(WNDPROC(lOldWndProc), hwnd, uMsg, wParam, lParam);
//}

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

void adminMainThread(void)
{
	traceLastFunc("adminMainThread()");
	static DWORD timer = 0;
	DWORD dwCurrentTime = GetTickCount();
#pragma region MassHP
	if (A_Set.bMassHP && dwCurrentTime - timer > 1150)
	{
		static unsigned short sPlId = 0;
		if (sPlId <= g_Players->ulMaxPlayerID)
		{
			if (g_Players->iIsListed[sPlId] && g_Players->pRemotePlayer[sPlId]->pPlayerData->pSAMP_Actor != nullptr)
			{
				say("/sethp %hu %d", sPlId, A_Set.iHpCount);
				addMessageToChatWindow("Игроку %s[%d] выдано %d HP", getPlayerName(sPlId), sPlId, A_Set.iHpCount);
				timer = dwCurrentTime;
			}
			sPlId++;
		}
		else
		{
			A_Set.bMassHP = false;
			sPlId = 0;
			addMessageToChatWindow("Выдача HP окончена");
			MessageBeep(MB_ICONEXCLAMATION);
		}
	}
#pragma endregion
#pragma region GiveGun
	if (A_Set.bGiveGuns && dwCurrentTime - timer > 1150)
	{
		static unsigned short sPlId = 0;
		static int iAmmo = 0;
		if (sPlId <= g_Players->ulMaxPlayerID)
		{
			if (!iAmmo)
				iAmmo = A_Set.iAmmoCount;

			if (g_Players->iIsListed[sPlId] && g_Players->pRemotePlayer[sPlId]->pPlayerData->pSAMP_Actor != nullptr)
			{
				if (iAmmo > 999)
				{
					say("/givegun %d %d 999", sPlId, A_Set.byteWeaponID);
					iAmmo -= 999;
				}
				else
				{
					say("/givegun %d %d %d", sPlId, A_Set.byteWeaponID, iAmmo);
					addMessageToChatWindow("Игроку %s[%d] выдано оружие", getPlayerName(sPlId), sPlId);
					sPlId++;
					iAmmo = A_Set.iAmmoCount;
				}
				timer = dwCurrentTime;
			}
			else
			{
				sPlId++;
				iAmmo = A_Set.iAmmoCount;
			}
		}
		else
		{
			A_Set.bGiveGuns = false;
			sPlId = 0;
			iAmmo = 0;
			addMessageToChatWindow("Выдача оружия окончена");
			MessageBeep(MB_ICONEXCLAMATION);
		}
	}
#pragma endregion
#pragma region GunSkills
	if (A_Set.bSkillGun && !A_Set.bGiveGuns)
	{
		A_Set.byteSkillWeaponID++;
		switch (A_Set.byteSkillWeaponID)
		{
		case 0: A_Set.iAmmoCount = 5500; A_Set.byteWeaponID = 31; A_Set.bGiveGuns = true; break;
		case 1: A_Set.iAmmoCount = 3500; A_Set.byteWeaponID = 24; A_Set.bGiveGuns = true; break;
		case 2: A_Set.iAmmoCount = 3500; A_Set.byteWeaponID = 25; A_Set.bGiveGuns = true; break;
		case 3: A_Set.iAmmoCount = 5500; A_Set.byteWeaponID = 29; A_Set.bGiveGuns = true;
		default:
			A_Set.bSkillGun = false;
			A_Set.byteSkillWeaponID = 0;
		}
	}
#pragma endregion
#pragma region TpPlayers
	if (A_Set.bMassTP && dwCurrentTime - timer > 1150 && !A_Set.PlayersIDForTP.empty())
	{
		USHORT& sPlId = A_Set.PlayersIDForTP.back();
		if (sPlId <= g_Players->ulMaxPlayerID)
		{
			say("/gethere %hu", sPlId);
		}
		A_Set.PlayersIDForTP.pop_back();
		timer = dwCurrentTime;
	}
#pragma endregion
	if (A_Set.traces && !A_Set.Tracers.empty())
	{
		if (dwCurrentTime - A_Set.Tracers.back().time > 2500)
		{
			A_Set.Tracers.pop_back();
		}
	}
}

void ResponsePasre(const std::string& resp, stIpInfo& IpInfo)
{
	traceLastFunc("RequestPasre()");
	Log(resp.c_str());
	size_t start = 9, end = resp.find('\"', start);
	IpInfo.City = resp.substr(start, end - start);
	start = end + 8;
	end = resp.find(',', start);
	IpInfo.pos[0] = std::stof(resp.substr(start, end - start));
	start = end + 7;
	end = resp.find(',', start);
	IpInfo.pos[1] = std::stof(resp.substr(start, end - start));
	start = end + 8;
	end = resp.find('\"', start);
	IpInfo.Provider = resp.substr(start, end - start);
}

void IpQuery(HINTERNET hSession, const std::string& ip_address, stIpInfo& IpInfo)
{
	traceLastFunc("IpQuery()");
	HINTERNET hURL = InternetOpenUrlA(hSession, ip_address.c_str(), nullptr, 0, 0, 0);
	if (hURL != nullptr)
	{
		DWORD dwSize = 0;
		InternetQueryDataAvailable(hURL, &dwSize, 0, 0);
		if (dwSize > 25)
		{
			try
			{
				char *szBuffer = new char[dwSize + 1];
				DWORD dwRead = 0;
				if (InternetReadFile(hURL, szBuffer, dwSize, &dwRead))
				{
					if (dwRead < dwSize)
						dwSize = dwRead;
					szBuffer[dwSize] = 0;
					ResponsePasre(szBuffer, IpInfo);
				}
				delete[] szBuffer;
			}
			catch (const std::bad_alloc &ex)
			{
				addMessageToChatWindow("Error mem alloc: %s", ex.what());
			}
		}
		InternetCloseHandle(hURL);
	}
}

void SravnenieIP(const std::string& reg_ip, const std::string& current_ip)
{
	if (!InternetCheckConnectionA("http://www.google.com", FLAG_ICC_FORCE_CONNECTION, 0))
	{
		addMessageToChatWindow("Error connection");
		return;
	}

	HINTERNET hSession = InternetOpenA("SAMP STEALER", INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
	if (hSession != nullptr)
	{
		stIpInfo IpInfo[2];
		IpQuery(hSession, "http://ip-api.com/json/" + reg_ip + "?fields=city,lat,lon,org", IpInfo[0]);
		IpQuery(hSession, "http://ip-api.com/json/" + current_ip + "?fields=city,lat,lon,org", IpInfo[1]);
		if (IpInfo[0].City != IpInfo[1].City)
		{
			addMessageToChatWindow("Reg City: %s | Current City: %s", IpInfo[0].City.c_str(), IpInfo[1].City.c_str());
			addMessageToChatWindow("Reg Provider: %s | Current Provider: %s", IpInfo[0].Provider.c_str(), IpInfo[1].Provider.c_str());
			addMessageToChatWindow("Distance: %.3f km", GeoDistance(IpInfo[0].pos, IpInfo[1].pos));
		}
		InternetCloseHandle(hSession);
	}
}

void addAdminCommand(char *name, CMDPROC function)
{
	if (name == nullptr || function == nullptr || g_Input == nullptr)
		return;

	if (g_Input->iCMDCount == (SAMP_MAX_CLIENTCMDS - 1))
	{
		Log("Error: couldn't initialize '%s'. Maximum command amount reached.", name);
		return;
	}

	if (strlen(name) > 30)
	{
		Log("Error: command name '%s' was too long.", name);
		return;
	}

	if (g_m0dCmdNum < (SAMP_MAX_CLIENTCMDS - 22))
	{
		g_m0dCmdNum++;
	}
	else
		Log("m0d_cmd_list[] too short.");

	((void(__thiscall *) (void *_this, char *command, CMDPROC function)) (g_dwSAMP_Addr + SAMP_FUNC_ADDCLIENTCMD)) (g_Input, name, function);
}