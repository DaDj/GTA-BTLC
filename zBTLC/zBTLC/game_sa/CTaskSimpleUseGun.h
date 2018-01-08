#pragma once

#include "plbase/PluginBase_SA.h"
#include "CTaskSimple.h"
#include "CVector.h"
#include "CVector2D.h"

enum eUseGunFlags : unsigned char
{
	USE_GUN_RIGHT_HAND = 1,
	USE_GUN_LEFT_HAND = 2
};

#pragma pack(push, 1)
class CTaskSimpleUseGun : public CTaskSimple
{
public:
	char field_8;
	char field_9;
	char field_A;
	char field_B;
	char field_C;
	union {
		eUseGunFlags m_nStateFlags;
		struct {
			unsigned char m_bRightHand : 1;
			unsigned char m_bLefttHand : 1;
		};
	};
	char field_E;
	char field_F;
	char field_10;
	char gap_11[3];
	CVector2D field_14;
	class CEntity *m_pTarget;
	CVector m_vTarget;
	void *m_pAnimBlendAssociation;
	class CWeaponInfo *m_pWeaponInfo;
	short field_34;
	short field_36;
	char field_38;
	char field_39;
	char field_3A;
	char field_3B;
};
#pragma pack(pop)

//VALIDATE_SIZE(CTaskSimpleUseGun, 0x3C);