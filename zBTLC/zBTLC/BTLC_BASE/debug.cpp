#include "debug.h"
#include <Windows.h>
#include "../Patch/MemoryMgr.h"
#include <sstream>
#include "../Events_SA/Events_SA.h"
#include "../game_sa/RenderWare.h"
#include "../game_sa/CFileLoader.h"
#include "../game_sa/CWorld.h"
#include "../game_sa/common.h"
#include "../game_sa/CHud.h"
#include "../game_sa/CTimer.h"
#include "../game_sa/CSprite.h"
#include "../game_sa/CFont.h"




namespace debug 
{
	void init()
	{
		debug_console();
		MemoryVP::InjectHook(0x405E0A, &CFileLoader::LoadObjectInstance_a,PATCH_CALL);
		MemoryVP::InjectHook(0x4062F2, &CFileLoader::LoadObjectInstance_a, PATCH_CALL);
		MemoryVP::InjectHook(0x5B892A, &CFileLoader::LoadObjectInstance_a, PATCH_CALL);


		plugin::Events::gameProcessEvent += []
		{
			
		};

		plugin::Events::drawHudEvent += []
		{
			draw_current_Modelname();
		};
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
		// If you have multiple screens, this will automatically move the co0nsole to the 2nd
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
		char string[40];
		CVector posn = FindPlayerCoors(-1);
		posn.z = posn.z - 5;
		CColPoint colp;
		CEntity *entity = 0;
		CWorld::ProcessVerticalLine(posn, posn.z + 100.0f, colp, entity, true, false, false, false, false, false, false);
		if (entity != 0)
		{
			CFont::SetColor(CRGBA::CRGBA(200, 200, 200, 255));
			sprintf(string, " Model: %s" ,CFileLoader::Objectnamelist[entity->m_wModelIndex].mName);
			CFont::SetFontStyle(FONT_SUBTITLES);
			CFont::SetAlignment(ALIGN_RIGHT);
			CFont::SetOutlinePosition(1);
			CFont::SetScale(CHud::x_fac(0.4f), CHud::y_fac(0.8f));
			CFont::PrintString(CHud::x_fac(635.0f), CHud::y_fac(5.0f), string);
		}
	}

	void create_IDE_LIST()
	{
	}


}

