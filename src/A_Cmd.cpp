#include "main.h"

void ACMD_MassHP(char *par)
{
	USHORT hp;
	if (sscanf_s(par, "%hu", &hp) > 0)
	{
		if (hp > 0 && hp < 256)
		{
			A_Set.bMassHP = true;
			A_Set.iHpCount = hp;
			addMessageToChatWindow("Выдача HP начата");
			MessageBeep(MB_ICONEXCLAMATION);
		}
	}
}

void ACMD_GiveGuns(char *par)
{
	USHORT ammo;
	BYTE weapon;
	if (sscanf_s(par, "%hhu %hu", &weapon, &ammo) > 1)
	{
		if (ammo > 0 && ammo < 30000 && weapon < 54)
		{
			A_Set.bGiveGuns = true;
			A_Set.byteWeaponID = weapon;
			A_Set.iAmmoCount = ammo;
			addMessageToChatWindow("Выдача оружия начата");
			MessageBeep(MB_ICONEXCLAMATION);
		}
	}
}

void ACMD_SkillGuns(char *par)
{
	addMessageToChatWindow("Выдача оружия на скиллы начата");
	A_Set.iAmmoCount = 5500; 
	A_Set.byteWeaponID = 31; 
	A_Set.bGiveGuns = true;
	A_Set.byteSkillWeaponID = 0;
	A_Set.bSkillGun = true;
	MessageBeep(MB_ICONEXCLAMATION);
}

void ACMD_PlayerTP(char *par)
{
	if (strlen(par) > 0)
	{
		USHORT maxPlayers = 0;
		if (sscanf_s(par, "%hu", &maxPlayers) && maxPlayers > 0 && maxPlayers <= g_Players->ulMaxPlayerID)
		{
			addMessageToChatWindow("Телепортирование %d игроков началось.", maxPlayers);
			A_Set.usMaxPlayerTP = maxPlayers;
			A_Set.bMassTP = true;
		}
		else
			addMessageToChatWindow("Ошибка параметров");
	}
}

void ACMD_PlayerTPBreak(char *)
{
	A_Set.usMaxPlayerTP = 0;
	A_Set.bMassTP = false;
	A_Set.PlayersIDForTP.clear();
	addMessageToChatWindow("Телепортирование прекращено");
}

void ACMD_IpInfo(char *par)
{
	if (strlen(par) > 0)
	{
		USHORT Id = 0;
		if (sscanf_s(par, "%hu", &Id))
		{
			say("/getip %d", Id);
		}
		else
			say("/agetip %s", par);
		A_Set.bIpInfo = true;
	}
}

void ACMD_trace(char *par)
{
	if (strlen(par) > 0)
	{
		if (!strncmp(par, "all", 3))
		{
			A_Set.bTraceAll = true;
			addMessageToChatWindow("Trace: All");
		}
		else
		{
			USHORT pID;
			if (sscanf_s(par, "%hu", &pID) && pID <= g_Players->ulMaxPlayerID)
			{
				A_Set.bTraceAll = false;
				A_Set.usTraceID = pID;
				addMessageToChatWindow("Trace: %d ID", pID);
			}
		}
        A_Set.bTraces = true;
	}
	else
	{
        A_Set.bTraces ^= true;
        addMessageToChatWindow("Trace: %s", A_Set.bTraces ? "on" : "off");
		if (!A_Set.bTraces)
		{
			A_Set.Tracers.clear();
		}
	}
}

void ACMD_changeKeyCombo(char *par)
{
    if (par != nullptr) {
        uint8_t tId;
        if (sscanf_s(par, "%hhu", &tId) == 1) {
            if (tId < A_Set.keycombo.size()) {
                parAdminSetting.keycomboId = tId;
                if (hhKeyKook == nullptr)
                {
                    hhKeyKook = SetWindowsHookExA(WH_KEYBOARD_LL, LLKeyProc, NULL, 0);
                    if (hhKeyKook == nullptr)
                        return addMessageToChatWindow("[!!!] Error set hook 0xX", GetLastError());
                }
                addMessageToChatWindow("Вы устанавливаете новые клавиши для \"%s\". Для завершения установки бинда нажмите ESC или ENTER.", A_Set.keycombo[tId].first.c_str());
                addMessageToChatWindow("Текущий бинд: \"%s\"", keycombo2String(A_Set.keycombo[tId].second).c_str());
            }
            else {
                addMessageToChatWindow("Выход за пределы!");
            }
        }
        else {
            addMessageToChatWindow("/changekey [index]");
        }
    }
}

void adminFunctions_cmds()
{
	addAdminCommand("masshp", ACMD_MassHP);
	addAdminCommand("massw", ACMD_GiveGuns);
	addAdminCommand("skweap", ACMD_SkillGuns);
	addAdminCommand("starttp", ACMD_PlayerTP);
	addAdminCommand("iip", ACMD_IpInfo);
	addAdminCommand("trace", ACMD_trace);
	addAdminCommand("endtp", ACMD_PlayerTPBreak);
    addAdminCommand("changekey", ACMD_changeKeyCombo);
}