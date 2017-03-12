#pragma once

struct Trace
{
	D3DXVECTOR3 start, end;
	DWORD color, time;
	Trace(float *st, float *en, DWORD col, DWORD tim)
	{
		start.x = st[0];
		start.y = st[1];
		start.z = st[2] - 0.2f;
		end.x = en[0];
		end.y = en[1];
		end.z = en[2];
		color = col;
		time = tim;
	}
};

struct CheckerPosition
{
	long x, y;
};

struct stIpInfo
{
	std::string City, Provider;
	float pos[2];
};

struct PlayerChecker
{
	std::string nick, reason;
};

struct AdminSetting
{
	std::vector<USHORT> PlayersIDForTP;
	std::vector<Trace> Tracers;
	std::vector<std::string> AdminChecker;
	std::vector<PlayerChecker> PlayerChecker;

	/*4 bytes*/
	CheckerPosition ACheckPos, PCheckPos, KillListPos;
	DWORD color_tracer_hit = 0xFFFF0000;
	DWORD color_tracer = 0xFF0000FF;
#pragma region ChatColor
	DWORD sms;
	DWORD report;
	DWORD reportr;
	DWORD support;
	DWORD feedback;
#pragma endregion
	int iHpCount = 100;
	int iAmmoCount = 100;

	/*2 bytes*/
	unsigned short usSetLeaderID = -1;
	unsigned short usMaxPlayerTP = 0;
	unsigned short usTraceID = 0;
	unsigned short usTraceMaxCount = 20;

	/*1 bytes*/
	unsigned char byteFrackID = 0;
	unsigned char byteWeaponID = 0;
	unsigned char byteSkillWeaponID = 0;

#pragma region ChatColorControl
	bool chatcolor = true;
	bool hud_indicator_chatcolors = true;
	bool chatcolors_sms = true;
	bool chatcolors_report = true;
	bool chatcolors_feedback = true;
	bool chatcolors_reportr = true;
	bool chatcolors_support = true;
#pragma endregion
	bool traces = true;
	bool bMassHP = false;
	bool bGiveGuns = false;
	bool bSkillGun = false;
	bool bMassTP = false;
	bool bTraceAll = true;
};

void initAdminSettings();
extern struct AdminSetting A_Set;