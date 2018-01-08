#pragma once

#include "plbase/PluginBase_SA.h"
#include "eWeaponType.h"

#pragma pack(push, 4)
class CWeapon
{
public:
	eWeaponType m_Type;
	unsigned int m_dwState;
	unsigned int m_dwAmmoInClip;
	unsigned int m_dwTotalAmmo;
	unsigned int m_dwTimeForNextShot;
	unsigned char field_14;
	unsigned char field_15;
	unsigned char field_16;
	unsigned char field_17;
	void *m_pParticle; // CParticle *

	bool HasWeaponAmmoToBeUsed();
};
#pragma pack(pop)

VALIDATE_SIZE(CWeapon, 0x1C);