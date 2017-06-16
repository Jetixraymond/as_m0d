#include "main.h"
#include <fstream>

struct AdminSetting A_Set;
struct stSettingParams parAdminSetting;
IniFile A_Ini(".\\" M0D_FOLDER ADMIN_INI_FILE);

void iniSetting();
void getAdminList();
void getPlayerList();

void initAdminSettings()
{
    traceLastFunc("initAdminSettings()");

    CreateDirectoryA(".\\" M0D_FOLDER "gangZones", 0);

    A_Set.dwColorTracerHit = 0xFFFF0000;
    A_Set.dwColorTracer = 0xFF0000FF;
    A_Set.dwColorSms = A_Set.dwColorReport = A_Set.dwColorReportr = A_Set.dwColorSupport = A_Set.dwColorFeedback = 0xFFFFFFFF;

    A_Set.iHpCount = A_Set.iAmmoCount = 100;

    A_Set.usSetLeaderID = -1;
    A_Set.usMaxPlayerTP = A_Set.usTraceID = 0;

    A_Set.byteFrackID = A_Set.byteWeaponID = A_Set.byteSkillWeaponID = 0;

    A_Set.bChatcolor = A_Set.bHudIndicatorChatcolors = A_Set.bChatcolorsSms = A_Set.bChatcolorsReport = 
    A_Set.bChatcolorsFeedback = A_Set.bChatcolorsReportr = A_Set.bChatcolorsSupport = true;
    A_Set.bHudIndicatorTrace = A_Set.bTraces = A_Set.bTraceAll = true;
    A_Set.bMassHP = false;
    A_Set.bGiveGuns = false;
    A_Set.bSkillGun = false;
    A_Set.bMassTP = false;
    A_Set.bChatID = true;
    A_Set.bIpInfo = false;
    A_Set.bConnectLog = true;
    A_Set.bDisconnectLog = true;
    A_Set.aCheckerMsg = "\nНет админов в сети";
    A_Set.pCheckerMsg = "\nНет игроков в сети";

    A_Set.bLogBan = A_Set.bLogWarn = A_Set.bLogKillList = A_Set.bConnectLog = A_Set.bDisconnectLog = true;

    A_Set.keycombo = {
        std::make_pair("trace", keycombo{2, { VK_LMENU, 'Z' }})
    };

    A_Set.bHudPing = true;
    A_Set.fontName = "Tahoma";
    A_Set.byteFontHeight = 9;

    iniSetting();
    getAdminList();
    getPlayerList();

    A_Set.Tracers.reserve(A_Set.usTraceMaxCount);

    if (A_Set.bLogBan)
        A_Set.fLogBan = fopen(".\\" M0D_FOLDER "ban.log", "a");
    if (A_Set.bLogWarn)
        A_Set.fLogWarn = fopen(".\\" M0D_FOLDER "warn.log", "a");
    if (A_Set.bLogKillList)
        A_Set.fLogKillList = fopen(".\\" M0D_FOLDER "KillList.log", "a");
}

void iniSetting()
{
    traceLastFunc("iniSetting()");
    if (A_Ini.SectionExist("ControlColors"))
    {
        A_Set.bHudIndicatorChatcolors = A_Ini.GetBoolean("ControlColors", "hud");
        A_Set.bChatcolor = A_Ini.GetBoolean("ControlColors", "auto_chat");
        A_Set.bChatcolorsSms = A_Ini.GetBoolean("ControlColors", "sms");
        A_Set.bChatcolorsReport = A_Ini.GetBoolean("ControlColors", "report");
        A_Set.bChatcolorsFeedback = A_Ini.GetBoolean("ControlColors", "feedback");
        A_Set.bChatcolorsReportr = A_Ini.GetBoolean("ControlColors", "reportr");
        A_Set.bChatcolorsSupport = A_Ini.GetBoolean("ControlColors", "support");
    }
    else
    {
        A_Ini.SetBoolean("ControlColors", "hud", true);
        A_Ini.SetBoolean("ControlColors", "auto_chat", true);
        A_Ini.SetBoolean("ControlColors", "sms", true);
        A_Ini.SetBoolean("ControlColors", "report", false);
        A_Ini.SetBoolean("ControlColors", "feedback", false);
        A_Ini.SetBoolean("ControlColors", "reportr", true);
        A_Ini.SetBoolean("ControlColors", "support", true);
    }

    if (A_Ini.SectionExist("Colors"))
    {
        stringToD3DColor(A_Ini.GetString("Colors", "color_sms"), &A_Set.dwColorSms);
        stringToD3DColor(A_Ini.GetString("Colors", "color_report"), &A_Set.dwColorReport);
        stringToD3DColor(A_Ini.GetString("Colors", "color_reportr"), &A_Set.dwColorReportr);
        stringToD3DColor(A_Ini.GetString("Colors", "color_support"), &A_Set.dwColorSupport);
        stringToD3DColor(A_Ini.GetString("Colors", "color_feedback"), &A_Set.dwColorFeedback);
        
    }
    else
    {
        A_Ini.SetString("Colors", "color_sms", "FFFFFF");
        A_Ini.SetString("Colors", "color_report", "FFFFFF");
        A_Ini.SetString("Colors", "color_reportr", "FFFFFF");
        A_Ini.SetString("Colors", "color_support", "FFFFFF");
        A_Ini.SetString("Colors", "color_feedback", "FFFFFF");
        
    }

    if (A_Ini.SectionExist("Tracer"))
    {
        A_Set.bHudIndicatorTrace = A_Ini.GetBoolean("ControlColors", "hud");
        A_Set.usTraceMaxCount = A_Ini.GetInt("Tracer", "TraceMaxCount");
        A_Set.dwTraceTimer = A_Ini.GetInt("Tracer", "TraceTime_ms");
        stringToD3DColor(A_Ini.GetString("Tracer", "color_tracer"), &A_Set.dwColorTracer);
        stringToD3DColor(A_Ini.GetString("Tracer", "color_tracer_hit"), &A_Set.dwColorTracerHit);
    }
    else
    {
        A_Ini.SetBoolean("ControlColors", "hud", A_Set.bHudIndicatorTrace);
        A_Ini.SetInt("Tracer", "TraceMaxCount", (A_Set.usTraceMaxCount = 30));
        A_Ini.SetInt("Tracer", "TraceTime_ms", (A_Set.dwTraceTimer = 2500));
        A_Ini.SetString("Tracer", "color_tracer", "0000FF");
        A_Ini.SetString("Tracer", "color_tracer_hit", "FF0000");
    }

    if (A_Ini.SectionExist("Position"))
    {
        A_Set.aCheckPos.x = A_Ini.GetInt("Position", "AdminChecker_X");
        A_Set.aCheckPos.y = A_Ini.GetInt("Position", "AdminChecker_Y");
        A_Set.pCheckPos.x = A_Ini.GetInt("Position", "PlayerChecker_X");
        A_Set.pCheckPos.y = A_Ini.GetInt("Position", "PlayerChecker_Y");
        A_Set.killListPos.x = A_Ini.GetInt("Position", "KillList_X");
        A_Set.killListPos.y = A_Ini.GetInt("Position", "KillList_Y");
        A_Set.connectionPos.x = A_Ini.GetInt("Position", "Connection_X");
        A_Set.connectionPos.y = A_Ini.GetInt("Position", "Connection_Y");
    }
    else
    {
        A_Ini.SetInt("Position", "AdminChecker_X", (A_Set.aCheckPos.x = 10));
        A_Ini.SetInt("Position", "AdminChecker_Y", (A_Set.aCheckPos.y = 20 * (g_Chat->pagesize + 3)));
        A_Ini.SetInt("Position", "PlayerChecker_X", (A_Set.pCheckPos.x = pPresentParam.BackBufferWidth - pD3DFont->DrawLength("Нет игроков в сети")));
        A_Ini.SetInt("Position", "PlayerChecker_Y", (A_Set.pCheckPos.y = pPresentParam.BackBufferHeight - int(pD3DFont->DrawHeight()) * 6));
        A_Ini.SetInt("Position", "KillList_X", (A_Set.killListPos.x = pPresentParam.BackBufferWidth - 180));
        A_Ini.SetInt("Position", "KillList_Y", (A_Set.killListPos.y = 220));
        A_Ini.SetInt("Position", "Connection_X", (A_Set.connectionPos.x = 10));
        A_Ini.SetInt("Position", "Connection_Y", (A_Set.connectionPos.y = A_Set.aCheckPos.y - 40));
    }

    if (A_Ini.SectionExist("ControlFunc"))
    {
        A_Set.bChatID = A_Ini.GetBoolean("ControlFunc", "ChatID");
        A_Set.bLogBan = A_Ini.GetBoolean("ControlFunc", "LogBan");
        A_Set.bLogWarn = A_Ini.GetBoolean("ControlFunc", "LogWarn");
        A_Set.bLogKillList = A_Ini.GetBoolean("ControlFunc", "LogKillList");
        A_Set.bConnectLog = A_Ini.GetBoolean("ControlFunc", "ConnectLog");
        A_Set.bDisconnectLog = A_Ini.GetBoolean("ControlFunc", "DisconnectLog");
        A_Set.bHudPing = A_Ini.GetBoolean("ControlFunc", "PingHud");
    }
    else {
        A_Ini.SetBoolean("ControlFunc", "ChatID", A_Set.bChatID);
        A_Ini.SetBoolean("ControlFunc", "LogBan", A_Set.bLogBan);
        A_Ini.SetBoolean("ControlFunc", "LogWarn", A_Set.bLogWarn);
        A_Ini.SetBoolean("ControlFunc", "LogKillList", A_Set.bLogKillList);
        A_Ini.SetBoolean("ControlFunc", "ConnectLog", A_Set.bConnectLog);
        A_Ini.SetBoolean("ControlFunc", "DisconnectLog", A_Set.bDisconnectLog);
        A_Ini.SetBoolean("ControlFunc", "PingHud", A_Set.bHudPing);
    }

    if (A_Ini.SectionExist("Keys"))
    {
        for (auto &pair : A_Set.keycombo) {
            string2Keycombo(A_Ini.GetString("Keys", pair.first.c_str()), pair.second);
        }
    }
    else {
        for (auto &pair : A_Set.keycombo) {
            A_Ini.SetString("Keys", pair.first.c_str(), keycombo2String(pair.second).c_str());
        }
    }

    if (A_Ini.SectionExist("FontSetting")) {
        A_Set.byteFontHeight = uint8_t(A_Ini.GetInt("FontSetting", "MainHeight"));
        A_Set.fontName = A_Ini.GetString("FontSetting", "MainFontName");
        setFontParams(&pD3DFont, A_Set.fontName.c_str(), A_Set.byteFontHeight);
    }
    else {
        A_Ini.SetInt("FontSetting", "MainHeight", A_Set.byteFontHeight);
        A_Ini.SetString("FontSetting", "MainFontName", A_Set.fontName.c_str());
    }

    menu_free_all();
    menu_maybe_init();
}

void endKeyHook()
{
    if (UnhookWindowsHookEx(hhKeyKook))
        hhKeyKook = nullptr;
    if (!parAdminSetting.keycombo.empty()) {
        //сделать диалог подтверждения?
        keycombo &key = A_Set.keycombo[parAdminSetting.keycomboId].second;
        key.count = 0;
        std::string keys;
        for (auto &pair : parAdminSetting.keycombo) {
            key.key[key.count++] = pair.first;
            keys.append(pair.second + " ");
        }
        keys.pop_back();
        parAdminSetting.keycombo.clear();
        parAdminSetting.keycombo.shrink_to_fit();
        if (A_Ini.SetString("Keys", A_Set.keycombo[parAdminSetting.keycomboId].first.c_str(), keys.c_str()))
            addMessageToChatWindow("Вы устанавили новые клавиши для \"%s\" : \"%s\".", A_Set.keycombo[parAdminSetting.keycomboId].first.c_str(), keys.c_str());
        else
            addMessageToChatWindow("FAIL!!!!");
    }
}

void getAdminList()
{
    std::ifstream fileAdmins(".\\" M0D_FOLDER "CheckerAdmins.txt", std::ios::in);
    if (fileAdmins.is_open()) {
        std::string adminName;
        while (!fileAdmins.eof()) {
            fileAdmins >> adminName;
            A_Set.AdminChecker.push_back(adminName);
            adminName.clear();
        }
        fileAdmins.close();
    }
}

void getPlayerList()
{
    std::ifstream filePlayers(".\\" M0D_FOLDER "CheckerPlayers.txt", std::ios::in);
    if (filePlayers.is_open()) {
        std::string player;
        //std::regex playerRegex("^Name=\\[(\\w{3,20})\\] Reason=\\[(.*)\\]$");
        //std::smatch match;
        while (std::getline(filePlayers, player)) {
            //if (std::regex_match(player, match, playerRegex)) {
            //    addMessageToChatWindow("Regex: \"%d\"", match.size());
            //    addMessageToChatWindow("Regex1: \"%s\"", match[0].str().c_str());
            //    addMessageToChatWindow("Regex2: \"%s\"", match[1].str().c_str());
            //    A_Set.AdminChecker.emplace_back(match[1].str(), match[2].str());
            //}
            //else {
            //    addMessageToChatWindow("Строка не соответствует: \"%s\"", player.c_str());
            //}
            A_Set.PlayerChecker.emplace_back(player.substr(6, player.find_first_of(']') - 6), player.substr(player.find_first_of(']') + 10, player.find_last_of(']') - (player.find_first_of(']') + 10)));
            player.clear();
        }
        filePlayers.close();
    }
}