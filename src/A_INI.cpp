// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "main.h"

void IniFile::szGetPath(const char *filename)
{
	if (strncmp(filename, ".\\",3) == 0)
	{
		strcpy_s(this->szPath, filename);
		return;
	}

	char *path = new char[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, path);
	sprintf(this->szPath, "%s\\%s", path, filename);
	delete[] path;
}
#pragma region File
bool IniFile::FileExist()
{
	return ::GetFileAttributesA(this->szPath) != DWORD(-1);
}

void IniFile::FileCreate()
{
	FILE *fp = fopen(this->szPath, "w");
	if (fp != nullptr)
		fclose(fp);
}

bool IniFile::FileDelete()
{
	if (!FileExist())
		return true;
	return (bool)remove(this->szPath);
}
#pragma endregion
#pragma region Gets
char* IniFile::GetString(const char* section, const char* key)
{
	if (!FileExist())
		return nullptr;

	if (GetPrivateProfileStringA(section, key, nullptr, this->ret, sizeof(this->ret), this->szPath))
		return this->ret;

	return nullptr;
}

char* IniFile::GetString(const char* section, const char* key, unsigned short len)
{
    if (FileExist())
    {
        //char *ret = new char[len];
        if (GetPrivateProfileStringA(section, key, nullptr, ret, len, this->szPath))
            return ret;
    }

	//delete[] ret;
	return nullptr;
}

int IniFile::GetInt(const char* section, const char* key)
{
	return GetPrivateProfileIntA(section, key, 0, this->szPath);
}

float IniFile::GetFloat(const char* section, const char* key)
{
	float ret_val;
	if (sscanf(GetString(section, key), "%f", &ret_val))
		return ret_val;
	return 0;
}

bool IniFile::GetBoolean(const char* section, const char* key)
{
    const char *val = GetString(section, key);
    if (val != nullptr && (val[0] == 'T' || val[0] == 't'))
		return true;
	return false;
}
#pragma endregion
#pragma region Sets
bool IniFile::SetString(const char* section, const char* key, const char* value)
{
	if (value == nullptr || !strlen(value))
	{
		return false;
	}
	return (bool)WritePrivateProfileStringA(section, key, value, this->szPath);
}

bool IniFile::SetFloat(const char* section, const char* key, float value)
{
	return SetString(section, key, std::to_string(value).c_str());
}

bool IniFile::SetInt(const char* section, const char* key, int value)
{
	return SetString(section, key, std::to_string(value).c_str());
}

bool IniFile::SetBoolean(const char* section, const char* key, bool value)
{
	return SetString(section, key, value ? "true" : "false");
}

bool IniFile::XorBoolean(const char* section, const char* key)
{
	SetBoolean(section, key, GetBoolean(section, key) ^ true);
	return GetBoolean(section, key);
}
#pragma endregion
#pragma region Sections
bool IniFile::SectionExist(const char* section)
{
	return GetString(section, nullptr) != nullptr ? true : false;
}

bool IniFile::SectionDelete(const char* section)
{
    return (bool)WritePrivateProfileStringA(section, nullptr, nullptr, this->szPath);
}
#pragma endregion
#pragma region Keys
bool IniFile::KeyExist(const char* section, const char* key)
{
	return GetString(section, key) != nullptr ? true : false;
}

bool IniFile::KeyDelete(const char* section, const char* key)
{
    return (bool)WritePrivateProfileStringA(section, key, nullptr, this->szPath);
}
#pragma endregion
#pragma region GerArrays
std::vector <std::string> IniFile::GetArrayString(const char* section, const char* key)
{
	int keys_count = ::GetPrivateProfileSection(section, this->ret, 2047, this->szPath);
	for (int i = 0; i < keys_count; i++)
		if (this->ret[i] == '\0') this->ret[i] = '\\';

	std::string sBuffer = this->ret, szBuff;
	std::vector <std::string> keys_value;
	size_t first_splash = 0, next_splash = std::string::npos, unk = std::string::npos;
	while ((next_splash = sBuffer.find_first_of('\\')) != std::string::npos)
	{
		unk = sBuffer.find_first_of('=');
		szBuff = sBuffer.substr(first_splash, unk);
		if (!strcmp(szBuff.c_str(), key))
			keys_value.push_back(sBuffer.substr(unk + 1, next_splash - unk - 1));
		sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
	}

	return keys_value;
}
std::vector <int> IniFile::GetArrayInt(const char* section, const char* key)
{
	int keys_count = ::GetPrivateProfileSection(section, this->ret, 2048, this->szPath);
	for (int i = 0; i < keys_count; i++)
		if (this->ret[i] == '\0') this->ret[i] = '\\';

	std::string sBuffer = this->ret, szBuff;
	std::vector <int> keys_int_value;
	size_t first_splash = 0, next_splash = std::string::npos, unk = std::string::npos;
	while ((next_splash = sBuffer.find_first_of('\\')) != std::string::npos)
	{
		unk = sBuffer.find_first_of('=');
		szBuff = sBuffer.substr(first_splash, unk);
		if (!strcmp(szBuff.c_str(), key))
			keys_int_value.push_back(std::stoi(sBuffer.substr(unk + 1, next_splash - unk - 1)));
		sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
	}

	return keys_int_value;
}
std::vector <float> IniFile::GetArrayFloat(const char* section, const char* key)
{
	int keys_count = ::GetPrivateProfileSection(section, this->ret, 2048, this->szPath);
	for (int i = 0; i < keys_count; i++)
		if (this->ret[i] == '\0') this->ret[i] = '\\';

	std::string sBuffer = this->ret, szBuff;
	std::vector <float> keys_float_value;
	size_t first_splash = 0, next_splash = std::string::npos, unk = std::string::npos;
	while ((next_splash = sBuffer.find_first_of('\\')) != std::string::npos)
	{
		unk = sBuffer.find_first_of('=');
		szBuff = sBuffer.substr(first_splash, unk);
		if (!strcmp(szBuff.c_str(), key))
			keys_float_value.push_back(std::stof(sBuffer.substr(unk + 1, next_splash - unk - 1)));
		sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
	}

	return keys_float_value;
}

std::vector <std::string> IniFile::GetArrayString(const char* section)
{
	int keys_count = ::GetPrivateProfileSection(section, this->ret, 2048, this->szPath);
	for (int i = 0; i < keys_count; i++)
		if (this->ret[i] == '\0') this->ret[i] = '\\';

	std::string sBuffer = this->ret, szBuff;
	std::vector <std::string> keys_value;
	size_t first_splash = 0, next_splash = std::string::npos, unk = std::string::npos;
	while ((next_splash = sBuffer.find_first_of('\\')) != std::string::npos)
	{
		unk = sBuffer.find_first_of('=');
		szBuff = sBuffer.substr(first_splash, unk);
		keys_value.push_back(sBuffer.substr(unk + 1, next_splash - unk - 1));
		sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
	}

	return keys_value;
}
std::vector <int> IniFile::GetArrayInt(const char* section)
{
	int keys_count = ::GetPrivateProfileSection(section, this->ret, 2048, this->szPath);
	for (int i = 0; i < keys_count; i++)
		if (this->ret[i] == '\0') this->ret[i] = '\\';

	std::string sBuffer = this->ret, szBuff;
	std::vector <int> keys_int_value;
	size_t first_splash = 0, next_splash = std::string::npos, unk = std::string::npos;
	while ((next_splash = sBuffer.find_first_of('\\')) != std::string::npos)
	{
		unk = sBuffer.find_first_of('=');
		szBuff = sBuffer.substr(first_splash, unk);
		keys_int_value.push_back(std::stoi(sBuffer.substr(unk + 1, next_splash - unk - 1)));
		sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
	}

	return keys_int_value;
}
std::vector <float> IniFile::GetArrayFloat(const char* section)
{
	int keys_count = ::GetPrivateProfileSection(section, this->ret, 2048, this->szPath);
	for (int i = 0; i < keys_count; i++)
		if (this->ret[i] == '\0') this->ret[i] = '\\';

	std::string sBuffer = this->ret, szBuff;
	std::vector <float> keys_float_value;
	size_t first_splash = 0, next_splash = std::string::npos, unk = std::string::npos;
	while ((next_splash = sBuffer.find_first_of('\\')) != std::string::npos)
	{
		unk = sBuffer.find_first_of('=');
		szBuff = sBuffer.substr(first_splash, unk);
		keys_float_value.push_back(std::stof(sBuffer.substr(unk + 1, next_splash - unk - 1)));
		sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
	}

	return keys_float_value;
}

DWORD IniFile::GetArrayFloat(const char* section, float *_array)
{
	DWORD keys_count = ::GetPrivateProfileSection(section, this->ret, 2048, this->szPath), i = 0;
	for (i = 0; i < keys_count; i++)
		if (this->ret[i] == '\0') this->ret[i] = '\\';
	i = 0;

	std::string sBuffer = this->ret, szBuff;
	size_t first_splash = 0, next_splash = std::string::npos, unk = std::string::npos;
	while ((next_splash = sBuffer.find_first_of('\\')) != std::string::npos)
	{
		unk = sBuffer.find_first_of('=');
		szBuff = sBuffer.substr(first_splash, unk);
		_array[i] = std::stof(sBuffer.substr(unk + 1, next_splash - unk - 1));
		sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
		i++;
	}

	return i;
}
DWORD IniFile::GetArrayFloat(const char* section, float *_array, DWORD nMaxSize)
{
	DWORD keys_count = ::GetPrivateProfileSection(section, this->ret, 2048, this->szPath), i = 0;
	for (i = 0; i < keys_count; i++)
		if (this->ret[i] == '\0') this->ret[i] = '\\';

	std::string sBuffer = this->ret, szBuff;
	size_t first_splash = 0, next_splash = std::string::npos, unk = std::string::npos;
	for (i = 0; i < nMaxSize && (next_splash = sBuffer.find_first_of('\\')) != std::string::npos; i++)
	{
		unk = sBuffer.find_first_of('=');
		szBuff = sBuffer.substr(first_splash, unk);
		_array[i] = std::stof(sBuffer.substr(unk + 1, next_splash - unk - 1));
		sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
	}

	return i;
}
#pragma endregion
IniFile::IniFile(const char *filename, bool created)
{
	ZeroMemory(ret, sizeof(ret));
	szGetPath(filename);
	if (created && !FileExist())
		FileCreate();
}

IniFile::~IniFile()
{
	//delete[] this->szPath;
}