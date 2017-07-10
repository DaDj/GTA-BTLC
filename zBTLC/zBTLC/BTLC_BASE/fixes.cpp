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
#include "fixes.h"

namespace BUGFIX
{
	/// <summary>
	/// FIXES of various GTA:SA BUGS
	/// </summary>
	void init()
	{
		various();
		Set_Zonesvisited();
	}


	void various()
	{
		//Enables running on metal.
		MemoryVP::Patch(0x55E870, 0xC2C03366);
		MemoryVP::Patch(0x55E874, 0x0004);

		// Fix vehicle back lights both using light state 3 (SA bug)
		MemoryVP::Patch<BYTE>(0x6E1D4F, 2);

		//Disable "To stop Carl..." message.
		MemoryVP::Patch<char>(0x63E8DF, 0xEB);
		//No hunger
		MemoryVP::Nop(0x5700F0, 5);
		//No Tab stats
		MemoryVP::Patch<char>(0x58FC2C, 0xEB);
		//No gang gestures
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

		// DISABLE PLAYING REPLAYS
		MemoryVP::Patch<BYTE>(0x460390, 0xC3);
		MemoryVP::Patch<BYTE>(0x4600F0, 0xC3);
		MemoryVP::Patch<BYTE>(0x45F050, 0xC3);

		//// DISABLE CHEATS
		//MemoryVP::Patch<BYTE>(0x439AF0, 0xC3);
		//MemoryVP::Patch<BYTE>(0x438370, 0xC3);
		

		// Disable CStats::IncrementStat (returns at start of function)
		MemoryVP::Patch<BYTE>(0x55C180, 0xC3);
		// DISABLE STATS DECREMENTING
		MemoryVP::Nop(0x559FD5, 7);
		MemoryVP::Nop(0x559FEB, 7);
		// DISABLE STATS MESSAGES
		MemoryVP::Patch<BYTE>(0x55B980, 0xC3);
		MemoryVP::Patch<BYTE>(0x559760, 0xC3);

		//// Disable ped vehicles damage when flipped
		MemoryVP::Patch(0x6A776B, 0xD8DD);
		MemoryVP::Nop(0x6A776D, 4);

		//// Disable player vehicle damage when flipped
		MemoryVP::Patch(0x570E7F, 0xD8DD);
		MemoryVP::Nop(0x570E81, 4);

		////Lower Gunflash show time
		MemoryVP::Patch<BYTE>(0x8D2E88, 1);
		MemoryVP::Patch<BYTE>(0x8D2E90, 1);

		////Smooth Heahdlighttexure movement
		MemoryVP::Patch<float>(0x70C6A8 + 1, 0.0);
		////Smooth carshadow movement
		MemoryVP::Patch<float>(0x70C2D5 + 1, 0.0);
		
	}


	void Set_Zonesvisited()
	{
		//Sets all zones to vistied (I.E. disables the greyed out radar parts)
		char* ExploredTerritoriesArray = (char*)0xBA3730;
		for (ExploredTerritoriesArray; ExploredTerritoriesArray <= (char*)0xBA3793; ExploredTerritoriesArray++)
			*ExploredTerritoriesArray = 1;
		//Nops to prevent reset when staring an new game.
		MemoryVP::Nop(0x53C590, 14);
		MemoryVP::Nop(0x5726B5, 14);
		MemoryVP::Nop(0x572111, 14);
	}

}