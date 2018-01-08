#pragma once

#include "plbase/PluginBase_SA.h"
#include "CAEAudioEntity.h"
#include "CAESound.h"

#pragma pack(push, 1)
class CWeaponAudio : public CAEAudioEntity
{
public:
	char field_7C;
	char field_7D;
	char field_7E;
	char field_7F;
	char field_80;
	char field_81[3];
	int field_84;
	int field_88;
	int field_8C;
	int field_90;
	int m_dwTimeChainsaw;
	int m_dwTimeLastFired;
	CAESound *m_pSounds;
	char m_bActive;
	char field_A1[3];
	class CPed *m_pPed;
};
#pragma pack(pop)

VALIDATE_SIZE(CWeaponAudio, 0xA8);