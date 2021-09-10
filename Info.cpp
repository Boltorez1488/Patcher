#include "Info.h"

HANDLE Info::_handle = GetCurrentProcess();
DWORD Info::_pID = GetCurrentProcessId();

DWORD Info::FindSignature(DWORD base, DWORD size, byte * sign, char * mask) {
	MEMORY_BASIC_INFORMATION mbi = { 0 };
	DWORD offset = 0;

	while (offset < size) {
		VirtualQueryEx(_handle, (LPCVOID)(base + offset), &mbi, sizeof(MEMORY_BASIC_INFORMATION));
		if (mbi.State != MEM_FREE) {
			byte* buffer = new byte[mbi.RegionSize];
			ReadProcessMemory(_handle, mbi.BaseAddress, buffer, mbi.RegionSize, NULL);
			for (size_t i = 0; i < mbi.RegionSize; i++) {
				if (DataCompare(buffer + i, sign, mask)) {
					delete[] buffer;
					return (DWORD)mbi.BaseAddress + i;
				}
			}
			delete[] buffer;
		}
		offset += mbi.RegionSize;
	}
	return 0;
}

bool Info::DataCompare(byte* data, byte* sign, char* mask) {
	for (; *mask; mask++, sign++, data++) {
		if (*mask == 'x' && *data != *sign)
			return false;
	}
	return true;
}

MODULEENTRY32* Info::GetModuleInfo(char* moduleName, bool about_process) {
	MODULEENTRY32* mInfo = new MODULEENTRY32;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _pID);
	mInfo->dwSize = sizeof(MODULEENTRY32);

	if (Module32First(snapshot, mInfo)) {
		if (about_process) { CloseHandle(snapshot); return mInfo; }
		while (Module32Next(snapshot, mInfo)) {
			if (_stricmp(moduleName, mInfo->szModule) == 0) {
				CloseHandle(snapshot);
				return mInfo;
			}
		}
	}
	CloseHandle(snapshot);
	memset(mInfo, 0, sizeof(MODULEENTRY32));
	delete mInfo;
	return nullptr;
}

DWORD Info::GetPointer(DWORD base, std::vector<DWORD> offsets) {
	for (auto offset : offsets) {
		base = *reinterpret_cast<DWORD*>(base + offset);
	}
	return base + offsets.back();
}
