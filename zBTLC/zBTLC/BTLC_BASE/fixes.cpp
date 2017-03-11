//////////////////////////////////////////////////////////////////
////              SAN ANDREAS - BUGFIXES					  ////
//////////////////////////////////////////////////////////////////
//// Author: D4DJ         VERSION: 2.0    DATE: 02.08.2016    ////
//////////////////////////////////////////////////////////////////
//// Description:                                             ////
//// A shitload of bugfixes.                                  ////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include <Windows.h>
#include "../Patch/MemoryMgr.h"
#include <iostream>

namespace BUGFIX
{
	/// <summary>
	/// FIXES of various GTA:SA BUGS
	/// </summary>
	void various()
	{
		//Enables running on metal.
		//	*(DWORD *)0x55E870 = 0xC2C03366;
		//	*(WORD *)0x55E874 = 0x0004;

		// Fix vehicle back lights both using light state 3 (SA bug)
		//	*(BYTE *)0x6E1D4F = 2;
	
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



		//DISABLE TASK::ROADCROSSLOOKAROUN
		//(HOTFIX FOR PATHS)
		MemoryVP::Nop(0x671CF0, 5);
		MemoryVP::Nop(0x671CF0, 5);
		MemoryVP::Patch<BYTE>(0x67448F, 0xEB);
		MemoryVP::Patch<BYTE>(0x6744A4, 0xEB);

		char* ExploredTerritoriesArray = (char*)0xBA3730;

		for (ExploredTerritoriesArray; ExploredTerritoriesArray <= (char*)0xBA3793; ExploredTerritoriesArray++)
			*ExploredTerritoriesArray = 1;

		MemoryVP::Nop(0x53C590, 14);
		MemoryVP::Nop(0x5726B5, 14);
		MemoryVP::Nop(0x572111, 14);

	}
}