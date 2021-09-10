#pragma once
#include <winnt.h>
#include <windows.h>

inline void erase_headers(HINSTANCE hModule1) {
	DWORD i, protect;

	if (!hModule1) return;

	const PIMAGE_DOS_HEADER pDoH = PIMAGE_DOS_HEADER(hModule1);
	const PIMAGE_NT_HEADERS pNtH = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<LONG>(hModule1) + reinterpret_cast<PIMAGE_DOS_HEADER>(hModule1)->e_lfanew);

	DWORD ersize = sizeof(IMAGE_DOS_HEADER);
	if (VirtualProtect(pDoH, ersize, PAGE_READWRITE, &protect)) {
		for (i = 0; i < ersize; i++)
			*static_cast<BYTE*>(reinterpret_cast<BYTE*>(pDoH) + i) = 0;
	}

	ersize = sizeof(IMAGE_NT_HEADERS);
	if (pNtH && VirtualProtect(pNtH, ersize, PAGE_READWRITE, &protect)) {
		for (i = 0; i < ersize; i++)
			*static_cast<BYTE*>(reinterpret_cast<BYTE*>(pNtH) + i) = 0;
	}
}

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _ModuleInfoNode {
	LIST_ENTRY LoadOrder;
	LIST_ENTRY InitOrder;
	LIST_ENTRY MemoryOrder;
	HMODULE baseAddress;
	unsigned long entryPoint;
	unsigned int size;
	UNICODE_STRING fullPath;
	UNICODE_STRING name;
	unsigned long flags;
	unsigned short LoadCount;
	unsigned short TlsIndex;
	LIST_ENTRY HashTable;
	unsigned long timestamp;
} ModuleInfoNode, *pModuleInfoNode;

typedef struct _ProcessModuleInfo {
	unsigned int size;
	unsigned int initialized;
	HANDLE SsHandle;
	LIST_ENTRY LoadOrder;
	LIST_ENTRY InitOrder;
	LIST_ENTRY MemoryOrder;
} ProcessModuleInfo, *pProcessModuleInfo;

#define UNLINK(x) (x).Blink->Flink = (x).Flink; \
	(x).Flink->Blink = (x).Blink;

inline bool hide_module(HMODULE hMod) {
	ProcessModuleInfo* pmInfo;
	ModuleInfoNode* module;

	_asm {
		mov eax, fs:[18h]
		mov eax, [eax + 30h]
		mov eax, [eax + 0Ch]
		mov pmInfo, eax
	}

	module = reinterpret_cast<ModuleInfoNode*>(pmInfo->LoadOrder.Flink);

	while (module->baseAddress && module->baseAddress != hMod) {
		module = reinterpret_cast<ModuleInfoNode*>(module->LoadOrder.Flink);
	}

	if (!module->baseAddress) {
		return false;
	}

	UNLINK(module->LoadOrder);
	UNLINK(module->InitOrder);
	UNLINK(module->MemoryOrder);
	UNLINK(module->HashTable);
	memset(module->fullPath.Buffer, 0, module->fullPath.Length);
	memset(module, 0, sizeof(ModuleInfoNode));

	return true;
}
