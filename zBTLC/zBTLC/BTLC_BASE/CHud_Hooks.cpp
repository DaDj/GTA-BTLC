
#include "../game_sa/plbase/PluginBase_SA.h"
#include "../game_sa/CHud.h"
#include "../game_sa/CRadar.h"
#include "../Patch/injector.hpp"
#include "CHud_Hooks.h"

namespace CHud_Hook
{
	void Init()
	{
		Rectangular_radar();
		MemoryVP::InjectHook(0x58FBD6, &CHud::DrawPlayerInfo, PATCH_CALL);
		MemoryVP::InjectHook(0x58AA50, &CHud::DrawZoneText, PATCH_JUMP);
		MemoryVP::InjectHook(0x58AEA0, &CHud::DrawCarName, PATCH_JUMP);
	}

	void Rectangular_radar()
	{
		//newradartoscreenspace
		MemoryVP::InjectHook(0x583480, &CRadar::TransformRadarPointToScreenSpace, PATCH_JUMP);
		//Draw radar mask
		MemoryVP::InjectHook(0x585700, &CRadar::DrawRadarMask, PATCH_JUMP);
		//replace original 
		MemoryVP::InjectHook(0x5832F0, &CRadar::LimitRadarPoint, PATCH_JUMP);

		//injector::MakeNOP(0x58AA25, 5);
		MemoryVP::Patch<float>(0x585719, 0.0f); // -1.0
		MemoryVP::Patch<float>(0x585721, 0.0f); // 1.0
		MemoryVP::Patch<float>(0x585729, 0.0f); // 1.0
		MemoryVP::Patch<float>(0x585731, 0.0f); // 1.0
		MemoryVP::Patch<float>(0x585739, 0.0f); // 1.0
		MemoryVP::Patch<float>(0x585741, 0.0f); // -1.0
		MemoryVP::Patch<float>(0x585749, 0.0f); // -1.0
		MemoryVP::Patch<float>(0x585751, 0.0f); // -1.0
		
		int alpha = 160;
		MemoryVP::Patch<int>(0x586432 + 1, alpha);
		MemoryVP::Patch<int>(0x58647B + 1, alpha);
		MemoryVP::Patch<int>(0x5864BC + 1, alpha);

		injector::MakeJMP(0x58A782, 0x58AA2A); //don't draw the borderthingy
		MemoryVP::Patch<BYTE>(0x58694E + 1, 1); //renderstatetexturalpha
		//MemoryVP::Patch<void*>(0x5834C0 + 2, &radar_width);
	}
	
}