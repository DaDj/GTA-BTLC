//////////////////////////////////////////////////////////////////
////           Back to Liberty City - Source              ////////
//////////////////////////////////////////////////////////////////
//// Author: D4DJ         VERSION: 2.0                    ////////
//////////////////////////////////////////////////////////////////
//// DATE: 31.07.2016                                     ////////
//////////////////////////////////////////////////////////////////
//// CHANGES: -included almost all classses ever needed   ////////
////          -recreated the whole source code            ////////
////          -disabled new weather effects for now       ////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
#pragma warning(disable:4067) 
#pragma warning(disable:4996) 
#pragma warning(disable:4244) 
#pragma warning(disable:4309) 

#include "stdafx.h"
#include "BTLC.h"
//#include <math.h>
//#include <ctime>
//#include "game_sa/RenderWare.h"



extern "C" __declspec(dllexport) 
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		Main(); // START BTLC FUNCTIONS
	}
	return TRUE;
}

