#pragma once

#include "plbase/PluginBase_SA.h"
#include "CWanted.h"
#include "CClothes.h"
#include "CVector.h"
#include "CVector2D.h"

#pragma pack(push, 4)
class CPlayerData
{
public:
	CWanted *m_pWanted;
	CClothes *m_pClothes;
	class CCopPed *m_pArrestingCop;
	CVector2D m_vFightMovement;
	float m_fMoveBlendRatio;
	float m_fTimeCanRun;
	float m_fSprintEnergy;
	unsigned char m_nChosenWeapon;
	unsigned char m_nCarDangerCounter;
	char _pad0[2];
	unsigned int m_dwStandStillTimer;
	unsigned int m_dwHitAnimDelayTimer;
	float m_fAttackButtonCounter;
	void *m_pDangerCar;
	unsigned int m_bStoppedMoving : 1;
	unsigned int m_bAdrenaline : 1;
	unsigned int m_bHaveTargetSelected : 1;             // Needed to work out whether we lost target this frame
	unsigned int m_bFreeAiming : 1;
	unsigned int m_bCanBeDamaged : 1;
	unsigned int m_bAllMeleeAttackPtsBlocked : 1;       // if all of m_pMeleeAttackers[] is blocked by collision, just attack straight ahead
	unsigned int m_JustBeenSnacking : 1;                // If this bit is true we have just bought something from a vending machine
	unsigned int m_bRequireHandleBreath : 1;
	unsigned int m_GroupStuffDisabled : 1;              // if this is true the player can't recrout or give his group commands.
	unsigned int m_GroupAlwaysFollow : 1;               // The group is told to always follow the player (used for girlfriend missions)
	unsigned int m_GroupNeverFollow : 1;                // The group is told to always follow the player (used for girlfriend missions)
	unsigned int m_bInVehicleDontAllowWeaponChange : 1; // stop weapon change once driveby weapon has been given
	unsigned int m_bRenderWeapon : 1;                   // set to false during cutscenes so that knuckledusters are not rendered
	unsigned int m_dwPlayerGroup;
	unsigned int m_dwAdrenalineEndTime;
	unsigned char m_bDrunkenness;
	unsigned char m_bFadeDrunkenness;
	unsigned char m_bDrugLevel;
	unsigned char m_bScriptLimitToGangSize;
	float m_fBreath;
	unsigned int m_dwMeleeWeaponAnimReferenced;
	unsigned int m_dwMeleeWeaponAnimReferencedExtra;
	float m_fFPSMoveHeading;
	float m_fLookPitch;
	float m_fSkateBoardSpeed;
	float m_fSkateBoardLean;
	struct RpAtomic *m_pSpecialAtomic;
	float m_fGunSpinSpeed;
	float m_fGunSpinAngle;
	unsigned int m_dwLastTimeFiring;
	unsigned int m_dwTargetBone;
	CVector m_vTargetBoneOffset;
	unsigned int m_dwBusFaresCollected;
	unsigned char m_bPlayerSprintDisabled;
	unsigned char m_bDontAllowWeaponChange;
	unsigned char m_bForceInteriorLighting;
	char _pad1;
	unsigned short m_wDPadDownPressedInMilliseconds;
	unsigned short m_wDPadUpPressedInMilliseconds;
	unsigned char m_bWetness;
	unsigned char m_bPlayersGangActive;
	unsigned char m_bWaterCoverPerc;
	char _pad2;
	float m_fWaterHeight;
	unsigned int m_dwFireHSMissilePressedTime;
	class CEntity *m_LastHSMissileTarget;
	unsigned int m_dwModelIndexOfLastBuildingShot;
	unsigned int m_dwLastHSMissileLOSTime : 31;
	unsigned int m_bLastHSMissileLOS : 1;
	class CPed *m_pCurrentProstitutePed;
	class CPed *m_pLastProstituteShagged;
};
#pragma pack(pop)

VALIDATE_SIZE(CPlayerData, 0xAC);