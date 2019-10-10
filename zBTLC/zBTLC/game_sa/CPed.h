#pragma once

#include "plbase/PluginBase_SA.h"
#include "ePedType.h"
#include "CPhysical.h"
#include "CPedCollisionAudio.h"
#include "CPedVoice.h"
#include "CWeaponAudio.h"
#include "CPedIntelligence.h"
#include "CPlayerData.h"
#include "AnimBlendFrameData.h"
#include "CPedAcquaintance.h"
#include "CPedIK.h"
#include "CWeapon.h"
#include "CVector2D.h"
#include "eWeaponType.h"
#include "ePedState.h"
#include "CAnimBlendAssociation.h"
#include "CModelInfo.h"


//enum ePedStats {
//
//};

enum eMoveState {

};

#pragma pack(push, 4)
class  CPed : public CPhysical {
protected:
	CPed(plugin::dummy_func_t) : CPhysical(plugin::dummy) {}
public:
	CPedCollisionAudio  m_CollisionAudio;
	CPedVoice           m_PedVoice;
	CWeaponAudio        m_WeaponAudio;
	char field_43C[36];
	char field_460[8];
	int field_468;
	/* https://code.google.com/p/mtasa-blue/source/browse/tags/1.3.4/MTA10/game_sa/CPedSA.h */
	unsigned int    m_bIsStanding : 1; // is ped standing on something
	unsigned int    m_bWasStanding : 1; // was ped standing on something
	unsigned int    m_bIsLooking : 1; // is ped looking at something or in a direction
	unsigned int    m_bIsRestoringLook : 1; // is ped restoring head postion from a look
	unsigned int    m_bIsAimingGun : 1; // is ped aiming gun
	unsigned int    m_bIsRestoringGun : 1; // is ped moving gun back to default posn
	unsigned int    m_bCanPointGunAtTarget : 1; // can ped point gun at target
	unsigned int    m_bIsTalking : 1; // is ped talking(see Chat())
	unsigned int    m_bInVehicle : 1; // is in a vehicle
	unsigned int    m_bIsInTheAir : 1; // is in the air
	unsigned int    m_bIsLanding : 1; // is landing after being in the air
	unsigned int    m_bHitSomethingLastFrame : 1; // has been in a collision last fram
	unsigned int    m_bIsNearCar : 1; // has been in a collision last fram
	unsigned int    m_bRenderPedInCar : 1; // has been in a collision last fram
	unsigned int    m_bUpdateAnimHeading : 1; // update ped heading due to heading change during anim sequence
	unsigned int    m_bRemoveHead : 1; // waiting on AntiSpazTimer to remove head
	unsigned int    m_bFiringWeapon : 1; // is pulling trigger
	unsigned int    m_bHasACamera : 1; // does ped possess a camera to document accidents
	unsigned int    m_bPedIsBleeding : 1; // Ped loses a lot of blood if true
	unsigned int    m_bStopAndShoot : 1; // Ped cannot reach target to attack with fist, need to use gun
	unsigned int    m_bIsPedDieAnimPlaying : 1; // is ped die animation finished so can dead now
	unsigned int    m_bStayInSamePlace :1; // when set, ped stays put
	unsigned int    m_bKindaStayInSamePlace :1; // when set, ped doesn't seek out opponent or cover large distances. Will still shuffle and look for cover
	unsigned int    m_bBeingChasedByPolice :1; // use nodes for routefind
	unsigned int    m_bNotAllowedToDuck :1; // Is this ped allowed to duck at all?
	unsigned int    m_bCrouchWhenShooting :1; // duck behind cars etc
	unsigned int    m_bIsDucking :1; // duck behind cars etc
	unsigned int    m_bGetUpAnimStarted :1; // don't want to play getup anim if under something
	unsigned int    m_bDoBloodyFootprints :1; // unsigned int bIsLeader :1;
	unsigned int    m_bDontDragMeOutCar :1;
	unsigned int    m_bStillOnValidPoly :1; // set if the polygon the ped is on is still valid for collision
	unsigned int    m_bAllowMedicsToReviveMe :1;
	unsigned int    m_bResetWalkAnims :1;
	unsigned int    m_bOnBoat :1; // flee but only using nodes
	unsigned int    m_bBusJacked :1; // flee but only using nodes
	unsigned int    m_bFadeOut :1; // set if you want ped to fade out
	unsigned int    m_bKnockedUpIntoAir :1; // has ped been knocked up into the air by a car collision
	unsigned int    m_bHitSteepSlope :1; // has ped collided/is standing on a steep slope (surface type)
	unsigned int    m_bCullExtraFarAway :1; // special ped only gets culled if it's extra far away (for roadblocks)
	unsigned int    m_bTryingToReachDryLand :1; // has ped just exited boat and trying to get to dry land
	unsigned int    m_bCollidedWithMyVehicle :1;
	unsigned int    m_bRichFromMugging :1; // ped has lots of cash cause they've been mugging people
	unsigned int    m_bChrisCriminal :1; // Is a criminal as killed during Chris' police mission (should be counted as such)
	unsigned int    m_bShakeFist :1; // test shake hand at look entity
	unsigned int    m_bNoCriticalHits : 1; // ped cannot be killed by a single bullet
	unsigned int    m_bHasAlreadyBeenRecorded : 1; // Used for replays
	unsigned int    m_bUpdateMatricesRequired : 1; // if PedIK has altered bones so matrices need updated this frame
	unsigned int    m_bFleeWhenStanding :1; //
	unsigned int    m_bMiamiViceCop :1;  //
	unsigned int    m_bMoneyHasBeenGivenByScript :1; //
	unsigned int    m_bHasBeenPhotographed :1;  //
	unsigned int    m_bIsDrowning : 1;
	unsigned int    m_bDrownsInWater : 1;
	unsigned int    m_bHeadStuckInCollision : 1;
	unsigned int    m_bDeadPedInFrontOfCar :1;
	unsigned int    m_bStayInCarOnJack :1;
	unsigned int    m_bDontFight :1;
	unsigned int    m_bDoomAim :1;
	unsigned int    m_bCanBeShotInVehicle : 1;
	unsigned int    m_bPushedAlongByCar :1; // ped is getting pushed along by car collision (so don't take damage from horz velocity)
	unsigned int    m_bNeverEverTargetThisPed :1;
	unsigned int    m_bThisPedIsATargetPriority :1;
	unsigned int    m_bCrouchWhenScared :1;
	unsigned int    m_bKnockedOffBike :1;
	unsigned int    m_bDonePositionOutOfCollision :1;
	unsigned int    m_bDontRender : 1;
	unsigned int    m_bHasBeenAddedToPopulation :1;
	unsigned int    m_bHasJustLeftCar :1;
	unsigned int    m_bIsInDisguise :1;
	unsigned int    m_bDoesntListenToPlayerGroupCommands :1;
	unsigned int    m_bIsBeingArrested :1;
	unsigned int    m_bHasJustSoughtCover :1;
	unsigned int    m_bKilledByStealth :1;
	unsigned int    m_bDoesntDropWeaponsWhenDead :1;
	unsigned int    m_bCalledPreRender :1;
	unsigned int    m_bBloodPuddleCreated : 1; // Has a static puddle of blood been created yet
	unsigned int    m_bPartOfAttackWave :1;
	unsigned int    m_bClearRadarBlipOnDeath :1;
	unsigned int    m_bNeverLeavesGroup :1; // flag that we want to test 3 extra spheres on col model
	unsigned int    m_bTestForBlockedPositions :1; // this sets these indicator flags for various posisions on the front of the ped
	unsigned int    m_bRightArmBlocked :1;
	unsigned int    m_bLeftArmBlocked :1;
	unsigned int    m_bDuckRightArmBlocked :1;
	unsigned int    m_bMidriffBlockedForJump :1;
	unsigned int    m_bFallenDown :1;
	unsigned int    m_bUseAttractorInstantly :1;
	unsigned int    m_bDontAcceptIKLookAts :1;
	unsigned int    m_bHasAScriptBrain : 1;
	unsigned int    m_bWaitingForScriptBrainToLoad : 1;
	unsigned int    m_bHasGroupDriveTask :1;
	unsigned int    m_bCanExitCar :1;
	unsigned int    m_CantBeKnockedOffBike :2; // 0=Default(harder for mission peds) 1=Never 2=Always normal(also for mission peds)
	unsigned int    m_bHasBeenRendered : 1;
	unsigned int    m_bIsCached :1;
	unsigned int    m_bPushOtherPeds :1; // GETS RESET EVERY FRAME - SET IN TASK: want to push other peds around (eg. leader of a group or ped trying to get in a car)
	unsigned int    m_bHasBulletProofVest :1;
	unsigned int    m_bUsingMobilePhone :1;
	unsigned int    m_bUpperBodyDamageAnimsOnly :1;
	unsigned int    m_bStuckUnderCar :1;
	unsigned int    m_bKeepTasksAfterCleanUp :1; // If true ped will carry on with task even after cleanup
	unsigned int    m_bIsDyingStuck :1;
	unsigned int    m_bIgnoreHeightCheckOnGotoPointTask :1; // set when walking round buildings, reset when task quits
	unsigned int    m_bForceDieInCar:1;
	unsigned int    m_bCheckColAboveHead:1;
	unsigned int    m_bIgnoreWeaponRange : 1;
	unsigned int    m_bDruggedUp : 1;
	unsigned int    m_bWantedByPolice : 1; // if this is set, the cops will always go after this ped when they are doing a KillCriminal task
	unsigned int    m_bSignalAfterKill: 1;
	unsigned int    m_bCanClimbOntoBoat :1;
	unsigned int    m_bPedHitWallLastFrame: 1; // useful to store this so that AI knows (normal will still be available)
	unsigned int    m_bIgnoreHeightDifferenceFollowingNodes: 1;
	unsigned int    m_bMoveAnimSpeedHasBeenSetByTask: 1;
	unsigned int    m_bGetOutUpsideDownCar :1;
	unsigned int    m_bJustGotOffTrain :1;
	unsigned int    m_bDeathPickupsPersist :1;
	unsigned int    m_bTestForShotInVehicle :1;
	unsigned int    m_bUsedForReplay : 1; // This ped is controlled by replay and should be removed when replay is done.
	/* */
	CPedIntelligence   *m_pIntelligence;
	CPlayerData        *m_pPlayerData;
	unsigned char     m_dwUsageType;
	AnimBlendFrameData *m_apBones[19];
	unsigned int    m_dwAnimGroup;
	CVector2D           m_vAnimMovingShiftLocal;
	CPedAcquaintance    m_Acquaintance;
	RwObject           *m_pWeaponObject;
	RwFrame            *m_pGunflashObject;
	RwObject           *m_pGogglesObject;
	unsigned char    *m_pGogglesState;
	short             m_wWeaponGunflashAlphaMP1;
	short field_506;
	short             m_wWeaponGunflashAlphaMP2;
	short field_50A;
	CPedIK              m_PedIK;
	int field_52C;
	ePedState           m_pedState; // see ePedState
	int             m_dwMoveState;
	int field_538;
	int field_53C;
	float               m_fHealth;
	float               m_fMaxHealth;
	float               m_fArmour;
	int field_54C;
	CVector2D           m_vAnimMovingShift;
	float               m_fCurrentRotation;
	float               m_fAimingRotation;
	float               m_fHeadingChangeRate;
	int field_564;
	int field_568;
	CVector field_56C;
	CVector field_578;
	CEntity            *m_pContactEntity;
	float field_588;
	class CVehicle    *m_pVehicle;
	int field_590;
	int field_594;
	int             m_nPedType;
	void               *m_pStats; // CPedStat *
	CWeapon             m_aWeapons[13];
	eWeaponType         m_eSavedWeapon; // when we need to hide ped weapon, we save it temporary here
	eWeaponType         m_eDelayedWeapon; // 'delayed' weapon is like an additional weapon, f.e., simple cop has a nitestick as current and pistol as delayed weapons
	unsigned int    m_dwDelayedWeaponAmmo;
	unsigned char     m_nActiveWeaponSlot;
	unsigned char     m_nWeaponShootingRate;
	unsigned char     m_nWeaponAccuracy;
	class CObject      *m_pTargetedObject;
	int field_720;
	int field_724;
	int field_728;
	char              m_nWeaponSkill;
	char              m_nFightingStyle;
	char              m_nAllowedAttackMoves;
	char field_72F;
	void               *m_pFire; // CFire *
	int field_734;
	int field_738;
	int field_73C;
	int             m_dwWeaponModelId;
	int field_744;
	int field_748;
	int field_74C;
	int             m_dwDeathTime;
	char              m_nBodypartToRemove;
	char field_755;
	short             m_wMoneyCount;
	int field_758;
	int field_75C;
	char              m_nLastWeaponDamage;
	CEntity            *m_pLastEntityDamage;
	int field_768;
	CVector             m_vTurretOffset;
	int             m_fTurretAngleA;
	int             m_fTurretAngleB;
	int             m_dwTurretPosnMode;
	int             m_dwTurretAmmo;
	void               *m_pCoverPoint; // CCoverPoint *
	void               *m_pEnex; // CEnEx *
	float               m_fRemovalDistMultiplier; // 1.0 by default
	short             m_wSpecialModelIndex;
	char field_796[2];
	int field_798;

	// class virtual functions


static	void My_Init();

	// Process applied anim
	void SetMoveAnim();
	// always returns true
	bool Save();
	// always returns true
	bool Load();

	// class functions
	
	bool PedIsInvolvedInConversation();
	bool PedIsReadyForConversation(bool arg0);
	bool PedCanPickUpPickUp();
	void CreateDeadPedMoney();
	void CreateDeadPedPickupCoors(float* pX, float* pY, float* pZ);
	void CreateDeadPedWeaponPickups();
	static void Initialise();
	void SetPedStats(ePedState statsType);
	void Update();
	void SetMoveState(eMoveState moveState);
	void SetMoveAnimSpeed(CAnimBlendAssociation* association);
	void StopNonPartialAnims();
	void RestartNonPartialAnims();
	bool CanUseTorsoWhenLooking();
	void SetLookFlag(float lookHeading, bool likeUnused, bool arg2);
	void SetLookFlag(CEntity* lookingTo, bool likeUnused, bool arg2);
	void SetAimFlag(CEntity* aimingTo);
	void ClearAimFlag();
	// Gets point direction relatively to ped
	int GetLocalDirection(CVector2D const& arg0);
	bool IsPedShootable();
	bool UseGroundColModel();
	bool CanPedReturnToState();
	bool CanSetPedState();
	bool CanBeArrested();
	bool CanStrafeOrMouseControl();
	bool CanBeDeleted();
	bool CanBeDeletedEvenInVehicle();
	void RemoveGogglesModel();
	int GetWeaponSlot(eWeaponType weaponType);
	void GrantAmmo(eWeaponType weaponType, unsigned int ammo);
	void SetAmmo(eWeaponType weaponType, unsigned int ammo);
	bool DoWeHaveWeaponAvailable(eWeaponType weaponType);
	bool DoGunFlash(int arg0, bool arg1);
	void SetGunFlashAlpha(bool rightHand);
	void ResetGunFlashAlpha();
	float GetBikeRidingSkill();
	void ShoulderBoneRotation(RpClump* clump);
	void SetLookTimer(unsigned int time);
	bool IsPlayer();
	void SetPedPositionInCar();
	void RestoreHeadingRate();
	static void RestoreHeadingRateCB(CAnimBlendAssociation* association, void* data);
	void SetRadioStation();
	void PositionAttachedPed();
	void Undress(char* modelName);
	void Dress();
	bool IsAlive();
	// dummy function
	void UpdateStatEnteringVehicle();
	// dummy function
	void UpdateStatLeavingVehicle();
	void GetTransformedBonePosition(RwV3d& inOffsetOutPosn, unsigned int boneId, bool updateSkinBones);
	void ReleaseCoverPoint();
	CTask* GetHoldingTask();
	CEntity* GetEntityThatThisPedIsHolding();
	void DropEntityThatThisPedIsHolding(unsigned char arg0);
	bool CanThrowEntityThatThisPedIsHolding();
	bool IsPlayingHandSignal();
	void StopPlayingHandSignal();
	float GetWalkAnimSpeed();
	void SetPedDefaultDecisionMaker();
	// limitAngle in radians
	bool CanSeeEntity(CEntity* entity, float limitAngle);
	bool PositionPedOutOfCollision(int arg0, CVehicle* arg1, bool arg2);
	bool PositionAnyPedOutOfCollision();
	bool OurPedCanSeeThisEntity(CEntity* entity, bool isSpotted);
	void SortPeds(CPed** pedList, int arg1, int arg2);
	void ClearLookFlag();
	float WorkOutHeadingForMovingFirstPerson(float heading);
	void UpdatePosition();
	void ProcessBuoyancy();
	bool IsPedInControl();
	void RemoveWeaponModel(int modelIndex);
	void AddGogglesModel(int modelIndex, bool* pGogglesType);
	void PutOnGoggles();
	char GetWeaponSkill(eWeaponType weaponType);
	void SetWeaponSkill(eWeaponType weaponType, char skill);
	void ClearLook();
	bool TurnBody();
	bool IsPointerValid();
	void GetBonePosition(RwV3d& outPosition, unsigned int boneId, bool updateSkinBones);
	CObject* GiveObjectToPedToHold(int modelIndex, unsigned char replace);
	void SetPedState(ePedState pedState);
	//1 = default, 2 = scm/mission script
	void SetCharCreatedBy(unsigned char createdBy);
	void CalculateNewVelocity();
	void CalculateNewOrientation();
	void ClearAll();
	void DoFootLanded(bool leftFoot, unsigned char arg1);
	void PlayFootSteps();
	void AddWeaponModel(int modelIndex);
	void TakeOffGoggles();
	void GiveWeapon(eWeaponType weaponType, unsigned int ammo, bool likeUnused);
	void SetCurrentWeapon(int slot);
	void SetCurrentWeapon(eWeaponType weaponType);
	void ClearWeapon(eWeaponType weaponType);
	void ClearWeapons();
	void RemoveWeaponWhenEnteringVehicle(int arg0);
	void ReplaceWeaponWhenExitingVehicle();
	void ReplaceWeaponForScriptedCutscene();
	void RemoveWeaponForScriptedCutscene();
	void GetWeaponSkill();
	void PreRenderAfterTest();
	void SetIdle();
	void SetLook(float heading);
	void SetLook(CEntity* entity);
	void Look();
	CEntity* AttachPedToEntity(CEntity* entity, CVector offset, unsigned short arg2, float arg3, eWeaponType weaponType);
	CEntity* AttachPedToBike(CEntity* entity, CVector offset, unsigned short arg2, float arg3, float arg4, eWeaponType weaponType);
	void DettachPedFromEntity();
	void SetAimFlag(float heading);
	bool CanWeRunAndFireWithWeapon();
	void RequestDelayedWeapon();
	void GiveDelayedWeapon(eWeaponType weaponType, unsigned int ammo);
	void GiveWeaponAtStartOfFight();
	void GiveWeaponWhenJoiningGang();
	bool GetPedTalking();
	void DisablePedSpeech(short arg0);
	void EnablePedSpeech();
	void DisablePedSpeechForScriptSpeech(short arg0);
	void EnablePedSpeechForScriptSpeech();
	void CanPedHoldConversation();
	void SayScript(int arg0, unsigned char arg1, unsigned char arg2, unsigned char arg3);
	void Say(unsigned short arg0, unsigned int arg1, float arg2, unsigned char arg3, unsigned char arg4, unsigned char arg5);
	void RemoveBodyPart(int boneId, char localDir);
	void SpawnFlyingComponent(int arg0, char arg1);
	bool DoesLOSBulletHitPed(CColPoint& colPoint);
	void RemoveWeaponAnims(int likeUnused, float blendDelta);
	bool IsPedHeadAbovePos(float zPos);
	void KillPedWithCar(CVehicle* car, float arg1, bool arg2);
	void MakeTyresMuddySectorList(CPtrList& ptrList);
	void DeadPedMakesTyresBloody();
	void My_ProcessAnimGroups();

    static void* operator new(unsigned int size);
    static void operator delete(void* data);
};
#pragma pack(pop)

VALIDATE_SIZE(CPed, 0x79C);

bool IsPedPointerValid(CPed* ped);
RwObject* SetPedAtomicVisibilityCB(RwObject* rwObject, void* data);
