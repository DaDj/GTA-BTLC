#include "CCopPed.h"
#include "CGeneral.h"

void CCopPed::My_Init()
{
	//Patch Call because the old one still exists and is called inside the fucntion.
	MemoryVP::InjectHook(0x46151A, &CCopPed::MySetCopWeapons, PATCH_CALL);
	MemoryVP::InjectHook(0x461541, &CCopPed::MySetCopWeapons, PATCH_CALL);
	MemoryVP::InjectHook(0x46759C, &CCopPed::MySetCopWeapons, PATCH_CALL);
	MemoryVP::InjectHook(0x469C9D, &CCopPed::MySetCopWeapons, PATCH_CALL);
	MemoryVP::InjectHook(0x47D8A8, &CCopPed::MySetCopWeapons, PATCH_CALL);
	MemoryVP::InjectHook(0x491CF5, &CCopPed::MySetCopWeapons, PATCH_CALL);
	MemoryVP::InjectHook(0x49973F, &CCopPed::MySetCopWeapons, PATCH_CALL);
	MemoryVP::InjectHook(0x61282F, &CCopPed::MySetCopWeapons, PATCH_CALL);
	MemoryVP::InjectHook(0x613830, &CCopPed::MySetCopWeapons, PATCH_CALL);
}

CCopPed* CCopPed::MySetCopWeapons(eCopType copType)
{
	((void(__thiscall *)(CCopPed*, eCopType))0x5DDC60)(this, copType);
	ClearWeapons();
	int iWeap = 0;
	switch (copType)
	{
	case COP_TYPE_CITYCOP:
	case COP_TYPE_LAPDM1:
		GiveWeapon(WEAPON_NIGHTSTICK, 1000, 1);
		GiveDelayedWeapon(WEAPON_PISTOL, 1000);
		//SetCurrentWeapon(WEAPON_PISTOL);
		break;
	case COP_TYPE_SWAT1:
	case COP_TYPE_SWAT2:
		 iWeap = CGeneral::GetRandomNumberInRange(0, 2);
		if (iWeap == 0)
		{
			GiveDelayedWeapon(WEAPON_PISTOL, 300);
			GiveDelayedWeapon(WEAPON_MP5, 200);
			GiveDelayedWeapon(WEAPON_M4, 150);
			SetCurrentWeapon(WEAPON_M4);
		}
		else if (iWeap == 1)
		{
			GiveDelayedWeapon(WEAPON_MP5, 1000);
			SetCurrentWeapon(WEAPON_MP5);
		}
		else 
		{
			GiveDelayedWeapon(WEAPON_SHOTGUN, 250);
			SetCurrentWeapon(WEAPON_SHOTGUN);
		}

	
		break;
	case COP_TYPE_FBI:
		GiveDelayedWeapon(WEAPON_PISTOL, 90);
		GiveDelayedWeapon(WEAPON_MP5, 900);
		SetCurrentWeapon(WEAPON_MP5);
		break;
	case COP_TYPE_ARMY:
		break;
	case COP_TYPE_CSHER:
		GiveWeapon(WEAPON_NIGHTSTICK, 1000, 1);
		GiveDelayedWeapon(WEAPON_PISTOL, 1000);
		//SetCurrentWeapon(WEAPON_PISTOL);
		break;
	default:
		break;
	}

	return this;
}



CCopPed::CCopPed(eCopType copType) : CPed(plugin::dummy) {
    ((void(__thiscall *)(CCopPed*, eCopType))0x5DDC60)(this, copType);

}

// Converted from thiscall void CCopPed::SetPartner(CCopPed *partner) 0x5DDE80
void CCopPed::SetPartner(CCopPed* partner)
{
	((void (__thiscall *)(CCopPed*, CCopPed*))0x5DDE80)(this, partner);
}

// Converted from thiscall void CCopPed::AddCriminalToKill(CPed *criminal) 0x5DDEB0
void CCopPed::AddCriminalToKill(CPed* criminal)
{
	((void (__thiscall *)(CCopPed*, CPed*))0x5DDEB0)(this, criminal);
}

// Converted from thiscall void CCopPed::RemoveCriminalToKill(CPed *,int criminalIdx) 0x5DE040
void CCopPed::RemoveCriminalToKill(CPed* arg0, int criminalIdx)
{
	((void (__thiscall *)(CCopPed*, CPed*, int))0x5DE040)(this, arg0, criminalIdx);
}

// Converted from thiscall void CCopPed::ClearCriminalsToKill(void) 0x5DE070
void CCopPed::ClearCriminalsToKill()
{
	((void (__thiscall *)(CCopPed*))0x5DE070)(this);
}