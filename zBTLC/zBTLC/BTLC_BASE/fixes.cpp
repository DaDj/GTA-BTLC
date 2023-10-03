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
#include "../game_sa/RenderWare.h"
#include "d3d9.h"
#include <math.h>
#include "../game_sa/CCamera.h"
#include "../game_sa/CMenuManager.h"
#include "../Events_SA/Events_SA.h"

namespace BUGFIX
{
	/// <summary>
	/// FIXES of various GTA:SA BUGS
	/// </summary>
	void init()
	{
		various();
		Set_Zonesvisited();

		plugin::Events::gameProcessEvent += []()
		{
			YSensitivityFix();
		};
	}


	void various()
	{
		////Sniper fucntions for cuntgun fun.
		//MemoryVP::Patch<BYTE>(0x685B7E + 2, 33);
		//// jumptable offset  
		//MemoryVP::Patch<BYTE>(0x742A30 + 33 - 16, 3);



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
		//(HOTFIX FOR PATHS) //will be disabled, bug is found in path generation
		//MemoryVP::Nop(0x671CF0, 5);
		//MemoryVP::Nop(0x671CF0, 5);
		//MemoryVP::Patch<BYTE>(0x67448F, 0xEB);
		//MemoryVP::Patch<BYTE>(0x6744A4, 0xEB);

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

		////PEDS stay in car at Death  --BUGGY (Autopilot doesnt recognize dead driver)
		//MemoryVP::Patch<int>(0x5E832C + 1, 0x21080);

		//// Disable wheel rotation after leaving vehicle
		MemoryVP::Nop(0x6B5579, 6);
		MemoryVP::Nop(0x6B568A, 6);

		////wheel trun speed
		MemoryVP::Patch<float>(0x871058, 0.1f);

		////More precise Rotations for placed objects --> change 0.5f to 0.000009.
		// Fixes that small rotations weren't done properly
		float* Float_001 = (float*)(0x858C14); //0.000009 float number
		MemoryVP::Patch<void*>(0x5381DC, &Float_001);
		MemoryVP::Patch<void*>(0x5381F2, &Float_001);


		//Longer Livetime time for broken stuff
		MemoryVP::Patch<int>(0x59D8BC, 1000);
		MemoryVP::Patch<int>(0x59E020, 250);

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

	void YSensitivityFix()
	{
		static float
			_flt_2_4 = 2.4f,
			_flt_1_8 = 1.8f;

		MemoryVP::Patch<void*>(0x0050FB06, &_flt_2_4);
		MemoryVP::Patch<void*>(0x00510BBB, &_flt_1_8);
		MemoryVP::Patch<void*>(0x00511DE4, &_flt_2_4);
		MemoryVP::Patch<void*>(0x0052227F, &_flt_2_4);
		MemoryVP::Patch<void*>(0x0050F022, &_flt_2_4);
		if ((float*)0x50F048 == &CCamera::m_fMouseAccelHorzntl)
		{
			MemoryVP::Patch<void*>(0x0050F048, &CCamera::m_fMouseAccelVertical);
			MemoryVP::Patch<void*>(0x0050FB28, &CCamera::m_fMouseAccelVertical);
			MemoryVP::Patch<void*>(0x00510C28, &CCamera::m_fMouseAccelVertical);
			MemoryVP::Patch<void*>(0x00511E0A, &CCamera::m_fMouseAccelVertical);
			MemoryVP::Patch<void*>(0x0052228E, &CCamera::m_fMouseAccelVertical);
		}

		MemoryVP::Patch<uint32_t>(0x005735E0, 0x00865450);

		MemoryVP::Patch<uint32_t>(0x005BC7B4, 0x1F0F6666);
		MemoryVP::Patch<uint32_t>(0x005BC7B8, 0x84);
		MemoryVP::Patch<uint16_t>(0x005BC7BC, 0x0);

		float hor = 0.0003125f + 0.0003125f / 2.0f;
		while (hor <= CCamera::m_fMouseAccelHorzntl)
		{
			hor += (0.005f / 16.0f);
		}
		hor -= 0.0003125f / 2.0f;
		if (hor != CCamera::m_fMouseAccelHorzntl)
		{
			CCamera::m_fMouseAccelHorzntl = hor;

			FrontEndMenuManager.SaveSettings();
		}
		hor *= (0.0015f / 0.0025f);
		CCamera::m_fMouseAccelVertical = hor;
	}
}

