#pragma once
//#include <windows.h>
//#include <string>
//#include <vector>

class IniFile
{
private:
	char szPath[1024];
	char ret[2048];
	void szGetPath(const char *filename);
public:
	IniFile(const char *filename,bool created=true);
	~IniFile();

	bool FileExist();
	void FileCreate();
	bool FileDelete();

	bool SectionExist(const char* section);
	bool SectionDelete(const char* section);

	bool KeyExist(const char* section, const char* key);
	bool KeyDelete(const char* section, const char* key);

	char* GetString(const char* section, const char* key);
	char* GetString(const char* section, const char* key, unsigned short len);
	int GetInt(const char* section, const char* key);
	float GetFloat(const char* section, const char* key);
	bool GetBoolean(const char* section, const char* key);

	bool SetString(const char* section, const char* key, const char* value);
	bool SetFloat(const char* section, const char* key, float value);
	bool SetInt(const char* section, const char* key, int value);
	bool SetBoolean(const char* section, const char* key, bool value);
	bool XorBoolean(const char* section, const char* key);

	std::vector <std::string> GetArrayString(const char* section, const char* key);
	std::vector <int> GetArrayInt(const char* section, const char* key);
	std::vector <float> GetArrayFloat(const char* section, const char* key);

	std::vector <std::string> GetArrayString(const char* section);
	std::vector <int> GetArrayInt(const char* section);
	std::vector <float> GetArrayFloat(const char* section);

	DWORD GetArrayFloat(const char* section, float *_array);
	DWORD GetArrayFloat(const char* section, float *_array, DWORD nMaxSize);
	
	//шаблоны: либо сразу реализация тут, либо подключать ini.cpp d ini.h (#include "ini.cpp"), но при этом ini.cpp не должен участвовать в сборке
	template<typename T>
	DWORD GetArrayInt(const char* section, T *_array)
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
			_array[i] = T(std::stoi(sBuffer.substr(unk + 1, next_splash - unk - 1)));
			sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
			i++;
		}

		return i;
	}
	template<typename T>
	DWORD GetArrayInt(const char* section, T *_array, DWORD nMaxSize)//ushort вместо T норм
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
			_array[i] = T(std::stoi(sBuffer.substr(unk + 1, next_splash - unk - 1)));
			sBuffer = sBuffer.substr(next_splash + 1, sBuffer.length());
		}

		return i;
	}
	
};