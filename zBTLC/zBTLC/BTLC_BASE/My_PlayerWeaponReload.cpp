#include "My_PlayerWeaponReload.h"
#include "../game_sa/CWeaponInfo.h"
#include "../Events_SA/Events_SA.h"
#include "../game_sa/CPed.h"
#include "../game_sa/CPad.h"
#include "../game_sa/common.h"
#include "../BTLC_BASE/other_shared.h"

namespace My_PlayerWeaponReload
{
	void init()
	{
		//FIXES/disables automatic weapon reload
		MemoryVP::Patch<char>(0x60B4DA, 0x83);
		MemoryVP::Patch<char>(0x60B4DA + 1, 0xC4);
		MemoryVP::Patch<char>(0x60B4DA + 2, 0x08);
		MemoryVP::Patch<char>(0x60B4DA + 3, 0xEB);
		MemoryVP::Patch<char>(0x60B4DA + 4, 0x21);

		plugin::Events::gameProcessEvent += []()
		{
			Reloadweapon();
		};
	}

	void Reloadweapon()
	{
		//TODO: allow sniper reload somehow && make R an setable key in the menu rework.
		CPed* Player = FindPlayerPed();
		//active weapon slot
		int activeweaponslot = Player->m_nActiveWeaponSlot;
		//get the info for the current weapon
		CWeaponInfo* Currentweapon = CWeaponInfo::GetWeaponInfo(Player->m_aWeapons[activeweaponslot].m_Type, Player->m_nWeaponSkill);

		//only allow reload if palyed presed "R" and the ammo in the mag is smaller than the max allowed ammo in the mag.
		if (KeyPressed('R') && Player->m_aWeapons[activeweaponslot].m_dwAmmoInClip < Currentweapon->m_wAmmoClip)
			Player->m_aWeapons[activeweaponslot].m_dwState = 2;
	}
}