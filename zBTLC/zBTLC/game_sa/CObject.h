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
