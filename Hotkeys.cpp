#include "Hotkeys.h"

Hotkeys::Hotkeys() {
	for (UINT i = 0x08; i < 0xE3; i++) {
		std::string key = Key(i);
		boost::to_upper(key);
		keys[key] = i;
	}
}

Hotkeys::~Hotkeys() {
}

void Hotkeys::keyscheck() {
	for each(auto k in manager) {
		for each(auto h in k.keys) {
			if (!states[h])
				goto nx;
		}
		k.function();
		nx: continue;
	}
}

bool Hotkeys::RegisterHotkeys(std::string hotkeys, boost::function<void()> f, std::string mark) {
	boost::replace_all(hotkeys, " ", "");
	boost::to_upper(hotkeys);
	boost::container::vector<std::string> hots;
	boost::split(hots, hotkeys, boost::is_any_of("+"));
	HotKey h;
	h.function = f;
	h.mark = mark;
	for each(auto s in hots) {
		if (s == "`") {
			s = "GRAVE";
		} else if (s == "CTRL") {
			s = "LEFTCONTROL";
		} else if(s == "ALT") {
			s = "LEFTALT";
		} else if(s == "SHIFT") {
			s = "LEFTSHIFT";
		} else if (s == "LCTRL") {
			s = "LEFTCONTROL";
		} else if (s == "LALT") {
			s = "LEFTALT";
		} else if (s == "LSHIFT") {
			s = "LEFTSHIFT";
		} else if (s == "RCTRL") {
			s = "RIGHTCONTROL";
		} else if (s == "RALT") {
			s = "RIGHTALT";
		} else if (s == "RSHIFT") {
			s = "RIGHTSHIFT";
		}
		auto code = keys[s];
		if (!code)
			return false;
		h.keys.push_back(code);
	}
	manager.push_back(h);
	return true;
}

std::string Hotkeys::Key(UINT code) {
	switch(code) {
		case(0x08): return "Backspace";
		case(0x09): return "Tab";
		case(0x0D): return "Return";
		case(0x10): return "LeftShift";
		case(0x11): return "LeftControl";
		case(0x12): return "LeftAlt";
		case(0x13): return "Pause";
		case(0x14): return "CapsLock";
		case(0x1B): return "Escape";
		case(0x20): return "Space";
		case(0x21): return "PageUp";
		case(0x22): return "PageDown";
		case(0x23): return "End";
		case(0x24): return "Home";
		case(0x25): return "ArrowLeft";
		case(0x26): return "ArrowUp";
		case(0x27): return "ArrowRight";
		case(0x28): return "ArrowDown";
		case(0x2D): return "Insert";
		case(0x2E): return "Delete";
		case(0x30): return "Zero";
		case(0x31): return "One";
		case(0x32): return "Two";
		case(0x33): return "Three";
		case(0x34): return "Four";
		case(0x35): return "Five";
		case(0x36): return "Six";
		case(0x37): return "Seven";
		case(0x38): return "Eight";
		case(0x39): return "Nine";
		case(0x41): return "A";
		case(0x42): return "B";
		case(0x43): return "C";
		case(0x44): return "D";
		case(0x45): return "E";
		case(0x46): return "F";
		case(0x47): return "G";
		case(0x48): return "H";
		case(0x49): return "I";
		case(0x4A): return "J";
		case(0x4B): return "K";
		case(0x4C): return "L";
		case(0x4D): return "M";
		case(0x4E): return "N";
		case(0x4F): return "O";
		case(0x50): return "P";
		case(0x51): return "Q";
		case(0x52): return "R";
		case(0x53): return "S";
		case(0x54): return "T";
		case(0x55): return "U";
		case(0x56): return "V";
		case(0x57): return "W";
		case(0x58): return "X";
		case(0x59): return "Y";
		case(0x5A): return "Z";
		case(0x5B): return "LeftWindows";
		case(0x5C): return "RightWindows";
		case(0x5D): return "AppMenu";
		case(0x5F): return "Sleep";
		case(0x60): return "Numpad0";
		case(0x61): return "Numpad1";
		case(0x62): return "Numpad2";
		case(0x63): return "Numpad3";
		case(0x64): return "Numpad4";
		case(0x65): return "Numpad5";
		case(0x66): return "Numpad6";
		case(0x67): return "Numpad7";
		case(0x68): return "Numpad8";
		case(0x69): return "Numpad9";
		case(0x6A): return "Multiply";
		case(0x6B): return "Add";
		case(0x6D): return "Subtract";
		case(0x6E): return "Decimal";
		case(0x6F): return "Slash";
		case(0x70): return "F1";
		case(0x71): return "F2";
		case(0x72): return "F3";
		case(0x73): return "F4";
		case(0x74): return "F5";
		case(0x75): return "F6";
		case(0x76): return "F7";
		case(0x77): return "F8";
		case(0x78): return "F9";
		case(0x79): return "F10";
		case(0x7A): return "F11";
		case(0x7B): return "F12";
		case(0x7C): return "F13";
		case(0x7D): return "F14";
		case(0x7E): return "F15";
		case(0x90): return "NumLock";
		case(0x91): return "ScrollLock";
		case(0x9A): return "SysRq";
		case(0xA0): return "LeftShift";
		case(0xA1): return "RightShift";
		case(0xA2): return "LeftControl";
		case(0xA3): return "RightControl";
		case(0xA6): return "WebBack";
		case(0xA7): return "WebForward";
		case(0xA8): return "WebRefresh";
		case(0xA9): return "WebStop";
		case(0xAA): return "WebSearch";
		case(0xAB): return "WebFavorites";
		case(0xAC): return "WebHome";
		case(0xAD): return "Mute";
		case(0xAE): return "VolumeDown";
		case(0xAF): return "VolumeUp";
		case(0xB0): return "NextTrack";
		case(0xB1): return "PrevTrack";
		case(0xB2): return "MediaStop";
		case(0xB3): return "PlayPause";
		case(0xB4): return "Mail";
		case(0xB5): return "MediaSelect";
		case(0xBA): return "Semicolon";
		case(0xBB): return "Equals";
		case(0xBC): return "Comma";
		case(0xBD): return "Minus";
		case(0xBE): return "Period";
		case(0xBF): return "Slash";
		case(0xC0): return "Grave";
		case(0xDB): return "LeftBracket";
		case(0xDC): return "Backslash";
		case(0xDD): return "RightBracket";
		case(0xDE): return "Apostrophe";
		case(0xE2): return "OEM_102";
		default: return "ERROR";
	}
}

bool Hotkeys::IsKeyDown(UINT code) {
	return (GetKeyState(code) & 0x8000) != 0;
}

bool Hotkeys::IsThisKeyDown(UINT code) {
	return states[code];
}

void Hotkeys::wnd_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch(uMsg) {
		case WM_KEYDOWN:
			states[wParam] = true;
			keyscheck();
			OnKeyDown(wParam);
			break;
		case WM_KEYUP:
			states[wParam] = false;
			OnKeyUp(wParam);
			break;
		default: 
			break;
	}
}

UINT Hotkeys::Code(std::string key) {
	boost::to_upper(key);
	return keys[key];
}

void Hotkeys::UnregisterMark(std::string mark) {
	for(size_t i = 0; i < manager.size(); i++) {
		if (manager[i].mark == mark)
			manager.erase(manager.begin() + i);
	}
}
