#pragma once
#include "plbase/PluginBase_SA.h"
#include "RenderWare.h"
#include "CColModel.h"
#include "C2dEffect.h"
#include "eModelID.h"

enum ModelInfoType : unsigned char
{
	MODEL_INFO_ATOMIC = 1,
	MODEL_INFO_TIME = 3,
	MODEL_INFO_WEAPON = 4,
	MODEL_INFO_CLUMP = 5,
	MODEL_INFO_VEHICLE = 6,
	MODEL_INFO_PED = 7,
	MODEL_INFO_LOD = 8
};

enum eModelInfoSpecialType : unsigned __int8 {
	TREE = 1,
	PALM = 2,
	GLASS_TYPE_1 = 4,
	GLASS_TYPE_2 = 5,
	TAG = 6,
	GARAGE_DOOR = 7,
	CRANE = 9,
	UNKNOWN = 10,
	BREAKABLE_STATUE = 11,
};

struct tTimeInfo
{
	unsigned char m_nTimeOn;
	unsigned char m_nTimeOff;
	signed short  m_wOtherTimeModel;
};

VALIDATE_SIZE(tTimeInfo, 4);

// originally an abstract class
#pragma pack(push, 4)
class  CBaseModelInfo {
public:
	unsigned int   m_dwKey;
	unsigned short m_wUsageCount;
	signed short   m_wTxdIndex;
	unsigned char  m_nAlpha; // 0 - 255
	unsigned char  m_n2dfxCount;
    short          m_w2dfxIndex;
    short          m_wObjectInfoIndex;
	union {
		uint16 m_nFlags;
		struct {
			uint8 m_nFlagsUpperByte;
			uint8 m_nFlagsLowerByte;
		};
		struct {
			/* https://github.com/multitheftauto/mtasa-blue/blob/master/Client/game_sa/CModelInfoSA.h */
			uint8 bHasBeenPreRendered : 1; // we use this because we need to apply changes only once
			uint8 bDrawLast : 1;
			uint8 bAdditiveRender : 1;
			uint8 bDontWriteZBuffer : 1;
			uint8 bDontCastShadowsOn : 1;
			uint8 bDoWeOwnTheColModel : 1;
			uint8 bIsBackfaceCulled : 1;
			uint8 bIsLod : 1;

			union {
				struct { // Atomic flags
					uint8 bIsRoad : 1;
					uint8 bAtomicFlag0x200 : 1;
					uint8 bDontCollideWithFlyer : 1;
					uint8 nSpecialType : 4;
					uint8 bWetRoadReflection : 1;
				};
				struct { // Vehicle flags
					uint8 bUsesVehDummy : 1;
					uint8 : 1;
							uint8 nCarmodId : 5;
							uint8 bUseCommonVehicleDictionary : 1;
				};
				struct { // Clump flags
					uint8 bHasAnimBlend : 1;
					uint8 bHasComplexHierarchy : 1;
					uint8 bAnimSomething : 1;
					uint8 bOwnsCollisionModel : 1;
					uint8 : 3;
					uint8 bTagDisabled : 1;
				};
			};
		};
	};
	CColModel        *m_pColModel;
	float             m_fDrawDistance;
	union {
		RwObject* m_pRwObject;
		RpClump*  m_pRwClump;
		RpAtomic* m_pRwAtomic;
	};

	// vtable

	class CBaseModelInfo *AsAtomicModelInfoPtr();
	class CBaseModelInfo *AsDamageAtomicModelInfoPtr();
	class CBaseModelInfo *AsLodAtomicModelInfoPtr();
	ModelInfoType GetModelType();//=0
	tTimeInfo *GetTimeInfo();
	void Init();
	void Shutdown();
	void DeleteRwObject();//=0
	unsigned int GetRwModelType();//=0
	struct RwObject *CreateInstance(RwMatrix *matrix);//=0
	struct RwObject *CreateInstance();//=0
	void SetAnimFile(char *filename);
	void ConvertAnimFileIndex();
	signed int GetAnimFileIndex();
	void IncreaseAlpha() {
		if (m_nAlpha >= 239)
			m_nAlpha = 255;
		else
			m_nAlpha += 16;
	};
	//
	void SetTexDictionary(char *txdName);
	void ClearTexDictionary();
	void AddTexDictionaryRef();
	void RemoveTexDictionaryRef();
	void AddRef();
	void RemoveRef();
	// initPairedModel defines if we need to set col model for time model
	void SetColModel(CColModel *colModel, bool initPairedModel);
	void Init2dEffects();
	void DeleteCollisionModel();
	// index is a number of effect (max number is (m_n2dfxCount - 1))
	C2dEffect *Get2dEffect(int index);
	void Add2dEffect(C2dEffect *effect);
	bool IsSwayInWind1()         const { return nSpecialType == eModelInfoSpecialType::TREE; };    // 0x0800
	bool IsSwayInWind2()         const { return nSpecialType == eModelInfoSpecialType::PALM; };              // 0x1000
	bool SwaysInWind()           const { return IsSwayInWind1() || IsSwayInWind2(); };

	bool IsGlassType1()          const { return nSpecialType == eModelInfoSpecialType::GLASS_TYPE_1; };      // 0x2000
	bool IsGlassType2()          const { return nSpecialType == eModelInfoSpecialType::GLASS_TYPE_2; };     // 0x2800
	bool IsGlass()               const { return IsGlassType1() || IsGlassType2(); };
	bool IsTagModel()            const { return nSpecialType == eModelInfoSpecialType::TAG; };              // 0x3000
	bool IsGarageDoor()          const { return nSpecialType == eModelInfoSpecialType::GARAGE_DOOR; };      // 0x3800
	bool IsBreakableStatuePart() const { return nSpecialType == eModelInfoSpecialType::BREAKABLE_STATUE; };
	bool IsCrane()               const { return nSpecialType == eModelInfoSpecialType::CRANE; };           // 0x4800         // 0x4800
    __parent_class_vtable__
};
#pragma pack(pop)

VALIDATE_SIZE(CBaseModelInfo, 0x20);