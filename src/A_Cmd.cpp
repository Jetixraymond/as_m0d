#include "main.h"

void adminFunctions_cmds()
{
	//����������� ������, �������
}

void ACMD_MassHP(char *par)
{
	addMessageToChatWindow("������ HP ������");
	MessageBeep(MB_ICONEXCLAMATION);
}

void ACMD_GiveGuns(char *par)
{
	addMessageToChatWindow("������ ������ ������");
	MessageBeep(MB_ICONEXCLAMATION);
}

void ACMD_SkillGuns(char *par)
{
	addMessageToChatWindow("������ ������ �� ������ ������");
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
		if (sscanf_s(par, "%hu", &maxPlayers) && maxPlayers > 0 && maxPlayers <= A_Set.usMaxPlayerID)
		{
			addMessageToChatWindow("���������������� %d ������� ��������.", maxPlayers);
			A_Set.usMaxPlayerTP = maxPlayers;
			A_Set.bMassTP = true;
		}
		else
			addMessageToChatWindow("������ ����������");
	}
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
			addMessageToChatWindow("������ ����������");
	}
}