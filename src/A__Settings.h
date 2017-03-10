#pragma once

struct AdminSetting
{
	/*4 bytes*/
	struct CheckerPosition
	{
		long x, y;
	} ACheckPos, PCheckPos, KillListPos;
	DWORD color_tracer_hit;
	DWORD color_tracer;
#pragma region ChatColor
	DWORD sms;
	DWORD report;
	DWORD reportr;
	DWORD support;
	DWORD feedback;
#pragma endregion

	/*2 bytes*/
	unsigned short usSetLeaderID = -1;

	/*1 bytes*/
	unsigned char byteFrackID = 0;

#pragma region ChatColorControl
	bool chatcolor = true;
	bool hud_indicator_chatcolors = true;
	bool chatcolors_sms = true;
	bool chatcolors_report = true;
	bool chatcolors_feedback = true;
	bool chatcolors_reportr = true;
	bool chatcolors_support = true;
#pragma endregion
	bool traces = false;
};

extern struct AdminSetting A_Set;