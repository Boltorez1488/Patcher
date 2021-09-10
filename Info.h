#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

class Info {
	static HANDLE _handle;
	static DWORD _pID;
public:
	static DWORD FindSignature(DWORD base, DWORD size, byte* sign, char* mask);
	static bool DataCompare(byte* data, byte* sign, char* mask);

	static MODULEENTRY32* GetModuleInfo(char* moduleName, bool about_process = false);
	static DWORD GetPointer(DWORD base, std::vector<DWORD> offsets);
};

