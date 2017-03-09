//////////////////////////////////////////////////////////////////
////           Back to Liberty City - MAIN START              ////
//////////////////////////////////////////////////////////////////
//// Author: D4DJ                                             ////
//////////////////////////////////////////////////////////////////
//// DATE: 31.07.2016                                         ////
//////////////////////////////////////////////////////////////////
//// CHANGES: -included almost all classses ever needed       ////
////          -recreated the whole source code                ////
////          -disabled new weather effects for now           ////
//////////////////////////////////////////////////////////////////
//// Description:                                             ////
//// This file will initiate the BTLC modiffications.         ////
//// SOME general modification are done in the main function. ////
//// Please keep the main function clean and use new functions////
//// instead.                                                 ////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#define DEBUG 
float VERSION = 0.20f;

#include "BTLC_BASE\fixes.h"
#include "BTLC_BASE\weather.h"
#include "BTLC_BASE\visuals.h"
#include "BTLC_BASE\limits.h"
#include "BTLC_BASE\windowmode.h"
#include "BTLC_BASE\fast_load.h"
#include "BTLC_BASE\CTrafficlights.h"
#include "game_sa\CObject.h"
#include "game_sa\CHud.h"
#include "BTLC_BASE\CHud_Hooks.h"



void debug_console();
void btlc_init(); //BTLC INIT
void check_gameversion();
void ParseCommandlineArgument(int thing, char* pArg);
void Function_starter();


void Main()
{
#ifdef DEBUG
	debug_console();	//debug console
	std::cout << std::endl;
	std::cout << "GTA:BACK TO LIBERTY CITY" << std::endl;
	std::cout << "developed by: D4DJ,  Majorapplepie" << std::endl << std::endl;
	std::cout << "Version: " << VERSION << " >DEBUG" << std::endl;
	std::cout << "COMPILED: " << __TIMESTAMP__ << std::endl << std::endl;
#endif // DEBUG

	//COMMANDLINE READER
	MemoryVP::InjectHook(0x74879A, &ParseCommandlineArgument, PATCH_CALL);
	MemoryVP::Patch(0x74877D, 0);
	////check game version
	check_gameversion();

	//START BTLC STUFF
	Function_starter();
}


void Function_starter()
{
	btlc_init();			////INIT OF BTLC
	fastload::Init();		//Fast loader
	BUGFIX::various();		////Fixes of some small GTA Bugs
	weather::init();		////Changes the weather effects.
	visuals::pickup_appearence();////Changes behaviour of Pickups
	visuals::init();		////VISUAL CHANGES init
	limits::IMG_LIMIT();	//Limit adjusting
	CHud_Hook::Init();			//New HUD init



	//Trafficlight changes
	CTrafficlights::Set_polygon_size(13);
	CTrafficlights::Set_Trafficlight_models();

	//New COP stream functions - ALL cops&copcars in all cities 
	//Copbikes are disabled cause they are annoying,duh.
	MemoryVP::InjectHook(0x40A150, &CStreaming::StreamCopModels, PATCH_JUMP);
	MemoryVP::InjectHook(0x407C00, &CStreaming::GetDefaultCopModel, PATCH_JUMP);
	MemoryVP::InjectHook(0x407C50, &CStreaming::GetDefaultCopCarModel, PATCH_JUMP);

	//New Masspoints for dynamic Objects
	MemoryVP::InjectHook(0x59F8A1, &CObject::SetObjectdata, PATCH_CALL);
}



//BTLC INIT
void btlc_init()
{
	////DECLARATION OF GENERAL CHANGES
	static  char	AppName[18] = "GTA:BTLC"; //new name of the GTA window.
	MemoryVP::Patch<void*>(0x619602 + 6, &AppName);
	static char  Userfiles[28] = "\\GTA BTLC User Files"; //new USER folder
	MemoryVP::Patch<void*>(0x74503F, &Userfiles);
	static  char  settingsfile[13] = "gta_btlc.set"; //new settings file
	MemoryVP::Patch<void*>(0x57C672, &settingsfile);
	MemoryVP::Patch<void*>(0x57C902, &settingsfile);
	MemoryVP::Patch<void*>(0x7489A0, &settingsfile);

	//Disable "To stop Carl..." message.
	MemoryVP::Patch<char>(0x63E8DF, 0xEB);
	// No hunger
	MemoryVP::Nop(0x5700F0, 5);
	//No Tab stats
	MemoryVP::Patch<char>(0x58FC2C, 0xEB);
	// No gang gestures
	MemoryVP::Patch<BYTE>(0x6601D7, 0xEB);
	MemoryVP::Patch<WORD>(0x660967, 0xE990);
	MemoryVP::Patch<BYTE>(0x66298F, 0xEB);
	MemoryVP::Patch<WORD>(0x6633C0, 0xE990);
	MemoryVP::Patch<BYTE>(0x663E4D, 0xEB);

	//Disabled Diving
	MemoryVP::Patch<BYTE>(0x688B36, 0xEB);



	//WINDOWPATCHES

	//MemoryVP::Patch<int>(0x74877D,0);
	//WINDOWMODE HOOKS
	//MemoryVP::Patch(0x74888F + 1, 0x10000000);
	//MemoryVP::Patch(0x7488B6 + 1, 0x10000000);
	//MemoryVP::Patch(0x7F89AC + 1, 0x10000000);
	//MemoryVP::Patch(0x745570 + 1, 0x10000000); //0x10000000
	MemoryVP::InjectHook(0x7461AA, &CVideomodemanager::GetNumSubSystems);
	MemoryVP::InjectHook(0x619D10, &psSelectDevice);
	MemoryVP::InjectHook(0x619BA6, &psSelectDevice);
	MemoryVP::InjectHook(0x6194B0, &psSelectDevice);
	MemoryVP::InjectHook(0x74629C, &FIND_VIDEOMODES);
	MemoryVP::InjectHook(0x745D3B, &FIND_VIDEOMODES);
	MemoryVP::InjectHook(0x57A05A, &FIND_VIDEOMODES);
	MemoryVP::InjectHook(0x57CFA7, &FIND_VIDEOMODES);
	////MemoryVP::InjectHook(0x748C1C, &changeresu);
	MemoryVP::InjectHook(0x748A1B, &changeresu);
	MemoryVP::InjectHook(0x7487A8, &INITINSTANCE);
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

void check_gameversion()
{
	// Find NT header
	uintptr_t          base = (uintptr_t)GetModuleHandleA(NULL);;
	IMAGE_DOS_HEADER*  dos = (IMAGE_DOS_HEADER*)(base);
	IMAGE_NT_HEADERS*  nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);
	int entryadress = base + nt->OptionalHeader.AddressOfEntryPoint;
	bool fail = 0;
	char* failtext  = "TestWindow";
	char* test = (char*)0x407610;

	switch (entryadress)
	{
	case 0x824570:  // GTA SA 1.0 US Compact //&and hoodlum?
		if (*test ==  (char)0xe9) 
		{
			failtext = "GTA SA 1.0 US Hoodlum not supported. \nPlease use GTA SA 1.0 US Compact";
			fail = 1;
			break;
		}
		std::cout << "EXE VERSION: COMPACT detected. -> start game" <<std::endl ;
		break;

	case 0x8245BC:  // GTA SA 1.0 EU Cracked (??????)
	case 0x8245B0:  // GTA SA 1.0 EU Cracked
		failtext = "GTA SA 1.0 EU Cracked not supported. \nPlease use GTA SA 1.0 US Compact";
		fail = 1;
		break;

	case 0x8252FC:  // GTA SA 1.1 US Cracked
		failtext = "GTA SA 1.0 US Cracked not supported. \nPlease use GTA SA 1.0 US Compact";
		fail = 1;
		break;

	case 0x82533C:  // GTA SA 1.1 EU Cracked
		failtext = "GTA SA 1.1 EU Cracked not supported. \nPlease use GTA SA 1.0 US Compact";
		fail = 1;
		break;

	case 0x85EC4A:  // GTA SA 3.0 (Cracked Steam Version)
		failtext = "GTA SA 3.0 (Cracked Steam Version) not supported. \nPlease use GTA SA 1.0 US Compact";
		fail = 1;
		break;

	case 0xD3C3DB:  // GTA SA 3.0 (Encrypted Steam Version)
		failtext = "GTA SA 3.0 (Encrypted Steam Version) not supported. \nPlease use GTA SA 1.0 US Compact";
		fail = 1;
		break;

	case 0x82457C:// GTA SA 1.0 US Cracked
		failtext = "GTA SA 1.0 US Cracked not supported. \nPlease use GTA SA 1.0 US Compact";
		fail = 1;
		break;

	default:
		failtext = "This Game EXE is not supported. \nPlease use GTA SA 1.0 US Compact";
		fail = 1;
		break;
	}

	if (fail == 1)
	{
		std::cout << "EXE VERSION: incompatible EXE detected. -> quit game" << std::endl;
		MessageBoxA(0, failtext, "GTA SA EXE not supported", MB_ICONWARNING);
		exit(0);
	}
}

void ParseCommandlineArgument(int thing, char* pArg)
{
	LPWSTR TEST = GetCommandLine();

	//Close game if it isn't launched via launcher
	if (!wcsstr(TEST, L"-launch"))
	{
		MessageBoxA(0, "Please use the GTA_BTLC Launcher to start this game.(GTA_BTLC.exe)", "BTLC - Launch", MB_ICONEXCLAMATION);
		exit(0);
		return;
	}

	if (pArg)
	{
		//settings for windowed mode
		if (!_stricmp(pArg, "-windowed"))
		{
			return;
		}

		//DEV enables the debug_consoles and outputs
		if (!_stricmp(pArg, "-DEV"))
		{
			return;
		}
	}
}
