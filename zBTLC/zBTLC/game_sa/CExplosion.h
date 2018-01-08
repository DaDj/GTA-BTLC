#pragma once

#include "plbase/PluginBase_SA.h"
#include "CVector.h"

enum eExplosionType : unsigned int
{
	EXPLOSION_GRENADE,
	EXPLOSION_MOLOTOV,
	EXPLOSION_ROCKET,
	EXPLOSION_WEAK_ROCKET,
	EXPLOSION_CAR,
	EXPLOSION_QUICK_CAR,
	EXPLOSION_BOAT,
	EXPLOSION_AIRCRAFT,
	EXPLOSION_MINE,
	EXPLOSION_OBJECT,
	EXPLOSION_TANK_FIRE,
	EXPLOSION_SMALL,
	EXPLOSION_RC_VEHICLE
};

#pragma pack(push,4)
class CExplosion
{
public:
	eExplosionType    m_Type;
	CVector           m_vPosition;
	float             m_fRadius;
	float             m_fPropagationRate;
	class CEntity    *m_pCreator;
	class CEntity    *m_pVictim;
	unsigned int  m_dwExpireTime;
	float             m_fDamagePercentage;
	bool              m_bIsActive;
	unsigned char   m_bActiveCounter;
	bool              m_bMakeSound;
	unsigned int  m_dwCreatedTime;
	unsigned int  m_dwParticlesExpireTime;
	float             m_fVisibleDistance;
	float             m_fGroundZ;
	unsigned int  m_dwFuelTimer; // goes down
	CVector           m_vFuelDirection[3];
	float             m_fFuelOffsetDistance[3];
	float             m_fFuelSpeed[3];

	// static functions

};
#pragma pack(pop)

// VALIDATE_OFFSET(CExplosion, m_bMakeSound, 0x2A);
VALIDATE_SIZE(CExplosion, 0x7C);