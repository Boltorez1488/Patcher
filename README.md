# Patcher
Old toolkit for C++ (x32)

Requires: Boost

Used:
- MHook
- AsmJit

Modules:
- Dll hider
- Int3, Hardware breakpoints
- AsmJit patcher place
- WinAPI hooker
- Signature scanner
- Hotkeys on WndProc with ASCII keys

## AsmJit Example
```
ASM(a);
a.mov(eax, 0x64);
a.jmp(0x1234);
Patcher::PlaceJit(&a, 0x4444);
```
