#pragma once

#include "plbase/PluginBase_SA.h"
#include "CVector.h"

#pragma pack(push, 4)
class CObjectInfo
{

public:
	float            m_fMass;
	float            m_fTurnMass;
	float            m_fAirResistance;
	float            m_fElasticity;
	float            m_fBuoyancyConstant;
	float            m_fUprootLimit;
	float            m_fColDamageMultiplier;
	unsigned char  m_nColDamageEffect;
	unsigned char  m_nSpecialColResponseCase;
	unsigned char  m_bCameraAvoidObject;
	unsigned char  m_bCausesExplosion;
	unsigned char  m_nFxType;
	CVector          m_vFxOffset;
	void            *m_pFxSystem; // CFxSystem *
	float            m_fSmashMultiplier;
	CVector          m_vBreakVelocity;
	float            m_fBreakVelocityRand;
	unsigned int m_dwGunBreakMode;
	unsigned int m_dwSparksOnImpact;
};

class CObjectdata
{
public:
	static CObjectInfo *ms_aObjectInfo;
};

#pragma pack(pop)

VALIDATE_SIZE(CObjectInfo, 0x50);