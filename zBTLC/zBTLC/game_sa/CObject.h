#pragma once

#include "plbase/PluginBase_SA.h"
#include "CPhysical.h"
#include "CObjectInfo.h"

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

class CDummyObject;

#pragma pack(push, 1)
class CObject : public CPhysical {
public:
	void               *m_pControlCodeList;
	unsigned char     m_nObjectType; // see enum eObjectType
	unsigned char     m_nBonusValue;
	unsigned short    m_wCostValue;
	unsigned int bObjectFlag0 : 1;
	unsigned int bObjectFlag1 : 1;
	unsigned int    m_bPickupPropertyForSale : 1;
	unsigned int    m_bPickupInShopOutOfStock : 1;
	unsigned int    m_bGlassBroken : 1;
	unsigned int bObjectFlag5 : 1;
	unsigned int    m_bIsExploded : 1;
	unsigned int bObjectFlag7 : 1;
	unsigned int    m_bIsLampPost : 1;
	unsigned int    m_bIsTargatable : 1;
	unsigned int    m_bIsBroken : 1;
	unsigned int    m_bTrainCrossEnabled : 1;
	unsigned int    m_bIsPhotographed : 1;
	unsigned int    m_bIsLiftable : 1;
	unsigned int    m_bIsDoorMoving : 1;
	unsigned int    m_bbIsDoorOpen : 1;
	unsigned int    m_bHasNoModel : 1;
	unsigned int    m_bIsScaled : 1;
	unsigned int    m_bCanBeAttachedToMagnet : 1;
	unsigned int bObjectFlag19 : 1;
	unsigned int bObjectFlag20 : 1;
	unsigned int bObjectFlag21 : 1;
	unsigned int    m_bFadingIn : 1;
	unsigned int    m_bAffectedByColBrightness : 1;
	unsigned int bObjectFlag24 : 1;
	unsigned int    m_bDoNotRender : 1;
	unsigned int    m_bFadingIn2 : 1;
	unsigned int bObjectFlag27 : 1;
	unsigned int bObjectFlag28 : 1;
	unsigned int bObjectFlag29 : 1;
	unsigned int bObjectFlag30 : 1;
	unsigned int bObjectFlag31 : 1;
	unsigned char     m_nColDamageEffect;
	unsigned char     m_nStoredColDamageEffect;
	char           field_146;
	char              m_nGarageDoorGarageIndex;
	unsigned char     m_nLastWeaponDamage;
	unsigned char     m_nColBrightness;
	short             m_nRefModelIndex;
	unsigned char     m_nCarColor[4]; // this is used for detached car parts
	int             m_dwRemovalTime; // time when this object must be deleted
	float               m_fHealth;
	float               m_fDoorStartAngle; // this is used for door objects
	float               m_fScale;
	CObjectInfo        *m_pObjectInfo;
	void               *m_pFire; // CFire *
	short             m_wScriptTriggerIndex;
	short             m_wRemapTxd; // this is used for detached car parts
	RwTexture          *m_pRemapTexture; // this is used for detached car parts
	CDummyObject       *m_pDummyObject; // used for dynamic objects like garage doors, train crossings etc.
	int             m_dwBurnTime; // time when particles must be stopped
	float               m_fBurnDamage;

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
};
#pragma pack(pop)

VALIDATE_SIZE(CObject, 0x17C);

bool IsObjectPointerValid_NotInWorld(CObject* object);
bool IsObjectPointerValid(CObject* object);
