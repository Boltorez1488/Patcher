#pragma once
#include <Windows.h>
#include <string>
#include <boost/signals2.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/container/map.hpp>
#include <boost/container/vector.hpp>

class Hotkeys {
	boost::container::map<UINT, bool> states;
	boost::container::map<std::string, UINT> keys;
public:
	Hotkeys();
	~Hotkeys();

	struct HotKey {
		boost::container::vector<UINT> keys;
		boost::function<void()> function;
		std::string mark;
	};

	boost::signals2::signal<void(UINT)> OnKeyUp;
	boost::signals2::signal<void(UINT)> OnKeyDown;

	UINT Code(std::string key);
	static std::string Key(UINT code);
	static bool IsKeyDown(UINT code);
	bool IsThisKeyDown(UINT code);

	bool RegisterHotkeys(std::string hotkeys, boost::function<void()> f, std::string mark);
	void UnregisterMark(std::string mark);

	void wnd_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	boost::container::vector<HotKey> manager;
	void keyscheck();
};

