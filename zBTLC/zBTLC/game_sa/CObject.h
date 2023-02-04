#pragma once

#include "plbase/PluginBase_SA.h"
#include "CPhysical.h"
#include "CObjectInfo.h"
#include "CPtrListDoubleLink.h"


struct structObject_masspoint
{
	char Modelname[32];
	int Modelindex;
	int Flag;
	float x;
	float y;
	float z;
};

enum eobjectflags 
{
	Object_Flag0 = 0x1,
	Object_Flag1 = 0x2,
	Object_PickupPropertyForSale = 0x4,
	Object_PickupInShopOutOfStock = 0x8,
	Object_GlassBroken = 0x10,
	Object_ObjectFlag5 = 0x20,
	Object_IsExploded = 0x40,
	Object_ObjectFlag7 = 0x80,
	Object_IsLampPost = 0x100,
	Object_IsTargatable = 0x200,
	Object_IsBroken = 0x400,
	Object_TrainCrossEnabled = 0x800,
	Object_IsPhotographed = 0x1000,
	Object_IsLiftable = 0x2000,
	Object_IsDoorMoving = 0x4000,
	Object_bIsDoorOpen = 0x8000,
	Object_HasNoModel = 0x10000,
	Object_IsScaled = 0x20000,
	Object_CanBeAttachedToMagnet = 0x40000,
	Object_ObjectFlag19 = 0x80000,
	Object_ObjectFlag20 = 0x100000,
	Object_ObjectFlag21 = 0x200000,
	Object_FadingIn = 0x400000,
	Object_AffectedByColBrightness = 0x800000,
	Object_ObjectFlag24 = 0x1000000,
	Object_DoNotRender = 0x2000000,
	Object_FadingIn2 = 0x4000000,
	Object_Flag27 = 0x8000000,
	Object_Flag28 = 0x10000000,
	Object_Flag29 = 0x20000000,
	Object_Flag30 = 0x40000000,
	Object_Flag31 = 0x80000000
 };

enum eObjectType {
    OBJECT_MISSION = 2,
    OBJECT_TEMPORARY = 3,
    OBJECT_MISSION2 = 6
};


class CObjectData;
class CDummyObject;
class CFire;

#pragma pack(push, 1)
class CObject : public CPhysical {
public:
	CPtrNodeDoubleLink* m_pControlCodeList;
	uint8               m_nObjectType; // see enum eObjectType
	uint8               m_nBonusValue;
	uint16              m_wCostValue;
	union {
		struct {
			uint32 bIsPickup : 1;               // 0x1
			uint32 b0x02 : 1;                   // 0x2 - collision related
			uint32 bPickupPropertyForSale : 1;  // 0x4
			uint32 bPickupInShopOutOfStock : 1; // 0x8
			uint32 bGlassBroken : 1;            // 0x10
			uint32 b0x20 : 1;                   // 0x20 - Something glass related, see `WindowRespondsToCollision`
			uint32 bIsExploded : 1;             // 0x40
			uint32 bChangesVehColor : 1;        // 0x80

			uint32 bIsLampPost : 1;
			uint32 bIsTargetable : 1;
			uint32 bIsBroken : 1;
			uint32 bTrainCrossEnabled : 1;
			uint32 bIsPhotographed : 1;
			uint32 bIsLiftable : 1;
			uint32 bIsDoorMoving : 1;
			uint32 bIsDoorOpen : 1;

			uint32 bHasNoModel : 1;
			uint32 bIsScaled : 1;
			uint32 bCanBeAttachedToMagnet : 1;
			uint32 bDamaged : 1;
			uint32 b0x100000 : 1;
			uint32 b0x200000 : 1;
			uint32 bFadingIn : 1; // works only for objects with type 2 (OBJECT_MISSION)
			uint32 bAffectedByColBrightness : 1;

			uint32 b0x1000000 : 1;
			uint32 bDoNotRender : 1;
			uint32 bFadingIn2 : 1;
			uint32 b0x08000000 : 1;
			uint32 b0x10000000 : 1;
			uint32 b0x20000000 : 1;
			uint32 b0x40000000 : 1;
			uint32 b0x80000000 : 1;
		} objectFlags;
		uint32 m_nObjectFlags;
	};
	uint8         m_nColDamageEffect;        // see eObjectColDamageEffect
	uint8         m_nSpecialColResponseCase; // see eObjectSpecialColResponseCases
	char          field_146;
	int8          m_nGarageDoorGarageIndex;
	uint8         m_nLastWeaponDamage;
	tColLighting  m_nColLighting;
	int16         m_nRefModelIndex;
	uint8         m_nCarColor[4];  // this is used for detached car parts
	uint32        m_nRemovalTime;  // time when this object must be deleted
	float         m_fHealth;
	float         m_fDoorStartAngle; // this is used for door objects
	float         m_fScale;
	CObjectInfo*  m_pObjectInfo;
	CFire*        m_pFire;
	int16         m_wScriptTriggerIndex;
	int16         m_wRemapTxd;     // this is used for detached car parts
	RwTexture*    m_pRemapTexture; // this is used for detached car parts
	CDummyObject* m_pDummyObject;  // used for dynamic objects like garage doors, train crossings etc.
	uint32        m_nBurnTime;     // time when particles must be stopped
	float         m_fBurnDamage;

	static uint16& nNoTempObjects;
	static float&  fDistToNearestTree;
	static bool&   bAircraftCarrierSamSiteDisabled;
	static bool&   bArea51SamSiteDisabled;

    // class functions

    void ProcessGarageDoorBehaviour();
    bool CanBeDeleted();
    void SetRelatedDummy(CDummyObject* relatedDummy);
    bool TryToExplode();
    void SetObjectTargettable(unsigned char targetable);
    bool CanBeTargetted();
    void RefModelInfo(int modelIndex);
    void SetRemapTexture(RwTexture* remapTexture, short txdIndex);
    float GetRopeHeight();
    void SetRopeHeight(float height);
    CEntity* GetObjectCarriedWithRope();
    void ReleaseObjectCarriedWithRope();
    void AddToControlCodeList();
    void RemoveFromControlCodeList();
    void ResetDoorAngle();
    void LockDoor();
    void Init();
    void DoBurnEffect();
    unsigned char GetLightingFromCollisionBelow();
    void ProcessSamSiteBehaviour();
    void ProcessTrainCrossingBehaviour();
    void ObjectDamage(float damage, CVector* fxOrigin, CVector* fxDirection, CEntity* damager, eWeaponType weaponType);
    void Explode();
    void ObjectFireDamage(float damage, CEntity* damager);
    
    void GrabObjectToCarryWithRope(CPhysical* attachTo);
    bool CanBeUsedToTakeCoverBehind();
    static class CObject* Create(int modelIndex);
    static class CObject* Create(CDummyObject* dummyObject);
    void ProcessControlLogic();

    // static functions

    static void SetMatrixForTrainCrossing(CMatrix* matrix, float arg1);
    static void TryToFreeUpTempObjects(int numObjects);
    static void DeleteAllTempObjects();
    static void DeleteAllMissionObjects();
    static void DeleteAllTempObjectsInArea(CVector point, float radius);

	static void SetObjectdata(int modelindex, CObject* object);
	static void ReadMasspoints(structObject_masspoint Result[]);

	bool IsFallenLampPost() const { return objectFlags.bIsLampPost && m_matrix->GetUp().z < 0.66F; }
	bool IsExploded() const { return objectFlags.bIsExploded; }

};
#pragma pack(pop)

VALIDATE_SIZE(CObject, 0x17C);

bool IsObjectPointerValid_NotInWorld(CObject* object);
bool IsObjectPointerValid(CObject* object);
