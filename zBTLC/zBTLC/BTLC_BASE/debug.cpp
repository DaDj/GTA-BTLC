#include "debug.h"
#include <Windows.h>
#include "../Patch/MemoryMgr.h"
#include <sstream>

namespace debug 
{
	void init()
	{
		debug_console();
	}
	
	void debug_console()
	{
		MemoryVP::InjectHook(0x821982, printf, PATCH_JUMP);
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CON", "w", stdout);
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stderr);
		int process = GetCurrentProcessId();
		// Screens
		// If you have multiple screens, this will automatically move the console to the 2nd
		if (GetSystemMetrics(SM_CMONITORS) > 1)
		{
			// Console Window
			HWND hConsole = GetConsoleWindow();
			RECT rect;
			GetWindowRect(hConsole, &rect);
			// Desktop
			HWND hDesktop = GetDesktopWindow();
			RECT rDesktopRect;
			GetWindowRect(hDesktop, &rDesktopRect);
			// Update Position
			SetWindowPos(hConsole, nullptr, rDesktopRect.right + 100, 150, rect.right - rect.left, rect.bottom - rect.top + 100, 0);
		}
	}

	void draw_current_Modelname()
	{

	}

	void create_IDE_LIST()
	{

	}

}

