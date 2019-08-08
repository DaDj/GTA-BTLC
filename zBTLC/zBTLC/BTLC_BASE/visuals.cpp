//////////////////////////////////////////////////////////////////
////              BTLC    VISUALS        					  ////
//////////////////////////////////////////////////////////////////
//// Author: D4DJ         VERSION: 2.0    DATE: 02.08.2016    ////
//////////////////////////////////////////////////////////////////
//// Description:                                             ////
//// changes of R* object appearences :					      ////
//// PICKUPS; HEADLIGHTS; DISTANCES                           ////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#include "../Patch/MemoryMgr.h"
#include "../Patch/injector.hpp"
#include "../game_sa/CVector2D.h"
#include <math.h>
namespace visuals
{
	void pickup_appearence()
	{
		//WEAPONPICKUP CHANGES
		static float
			pickup_rot_speed = 0.0f,
			pickup_size_mult = 0.0f,
			pickup_z_off = -0.3f,
			pickup_z_off_money = 0.2f;

		MemoryVP::Patch<void*>(0x454EA1 + 2, &pickup_rot_speed); //moneyrotation
		MemoryVP::Patch<void*>(0x455CD0 + 2, &pickup_rot_speed); //pickuprotation
		MemoryVP::Patch<void*>(0x455C9A + 2, &pickup_size_mult); //pickupsize
		MemoryVP::Patch<void*>(0x459255 + 2, &pickup_z_off);	//z_offset weapons
		MemoryVP::Patch<void*>(0x458A17 + 2, &pickup_z_off_money);	//z_offset money
		MemoryVP::Patch<char>(0x4568E4 + 1, 1);
		MemoryVP::Patch<float>(0x4568DD + 1, 0.0f);


	}

	void vehicle_headlights()
	{
		static float
			HeadlightCoronaDistance = 200.0f,
			DD_HLightSdw = 50.0,
			DD_HLightSdw2 = DD_HLightSdw / 1.5;


		MemoryVP::Patch<int>(0x6E0DEE, 110);//HeadlightCoronaAlpha
		MemoryVP::Patch<int>(0x6E0CF8, 110);//HeadlightCoronaAlpha
		MemoryVP::Patch<float>(0x6E0CA6, 0.5); //HeadlightCoronaSize
		MemoryVP::Patch<void*>(0x6E0C62 + 2, &HeadlightCoronaDistance); //HeadlightCoronaDistance

		MemoryVP::Patch<float>(0x872744, DD_HLightSdw*0.75);//Headlightsahdow distance
		MemoryVP::Patch<float>(0x872748, DD_HLightSdw *DD_HLightSdw);//Headlightshadowdistance 
		MemoryVP::Patch<float>(0x872740, ( 1 / (DD_HLightSdw * 0, 33)));//Headlightshadowdistance
		MemoryVP::Patch<void*>(0x70C5FE, &DD_HLightSdw2); //Headlightshadowdistance
	}



	void init()
	{
		pickup_appearence();
		vehicle_headlights();

		// No Heat Haze <-move to visuals
		MemoryVP::Patch<BYTE>(0x72C1B7, 0xEB);
		// Render the static shadow at every fxquality
		//MemoryVP::Patch<BYTE>(0x70BDAC, 0x84);

		//no Motion BLur
		MemoryVP::Patch<char>(0x704DBC + 1, 0xDB);//(DB)
		MemoryVP::Patch<char>(0x704DBC, 0x30);//(XOR)

		//Corona shadow distance
		MemoryVP::Patch<float>(0x6FD3A6, 80.0); 
		//ground distance
		//MemoryVP::Patch<float>(0x6FD368 + 4, 6.5);

			
		//Traffic/Lampost ground distance
		//MemoryVP::Patch<float>(0x70C89B +1, 5.0);

		//Traffic/Lampost shadow distance
			MemoryVP::Patch<float>(0x70C89C, 80.0);
			MemoryVP::Patch<float>(0x70C88B, 80.0);

		//Shadow distances////////////////////////////
		static float
			DD_shdw_veh = 200.0,
			DD_shdw_veh_quad = DD_shdw_veh*DD_shdw_veh,
			DD_shdw_ped = 150.0,
			DD_shdw_ped_quad = DD_shdw_ped * DD_shdw_ped;

		//vehicles
		MemoryVP::Patch<void*>(0x70BEA5 + 2, &DD_shdw_veh_quad);//0x70BEA5 + 2 //org 18*18 pointer
		MemoryVP::Patch<void*>(0x70BEB4 + 2, &DD_shdw_veh);//0x70BEB4 + 2 //org 18 pointer
		//Peds
		MemoryVP::Patch<float>(0x8D5240, DD_shdw_ped);//org 18.0 float
		MemoryVP::Patch<float>(0xC4B6B0, DD_shdw_ped_quad);//18.0 * 18.0


		//PED and VEHICLE DISTANCE/////////////////////
		static float
			DD_veh_LOD = 130.0f, //Drawdistance vehicle lod 70
			DESD_Veh_onscr = 200.0f,//despawn onscreen 170.0
			DESD_veh_offscr = 150.0f,//despawn offscreen 75.0
			DESD_veh_offscr_2 = DESD_veh_offscr * 0.6,
			DD_ped = 230.0f,	//drawdistance ped
			DESD_ped_onscr = 220.0f,
			DESD_ped_offscr = 180.0f,
			SD_ped_onscr = 60.5f,//spawn onsscreen
			SD_ped_offscr = 70.0f;

		MemoryVP::Patch<void*>(0x732926, &DD_veh_LOD);
		MemoryVP::Patch<void*>(0x732978, &DD_veh_LOD);
		MemoryVP::Patch<void*>(0x4250F0, &DESD_Veh_onscr);
		MemoryVP::Patch<float>(0x42510F, DESD_veh_offscr);
		MemoryVP::Patch<float>(0x4250E2, DESD_veh_offscr_2);
		
		MemoryVP::Patch<float>(0x86C850, SD_ped_onscr);
		MemoryVP::Patch<float>(0x86D284, SD_ped_offscr);
		MemoryVP::Patch<void*>(0x6120FF, &DESD_ped_onscr);
		MemoryVP::Patch<void*>(0x612128, &DESD_ped_offscr);
		MemoryVP::Patch<void*>(0x73295E, &DD_ped);
	
		//MemoryVP::Patch<void*>(0x612142, &drawD_Ped3);//0x612142 org. 25.0f
		//MemoryVP::Patch<void*>(0x431A24, &drawD_vehicle5);//0x431A24 org. 150.0f 
		//MemoryVP::Patch<float>(0x871008, drawD_Ped5);//0x871008 org. 10.0f patched 150
	}
}