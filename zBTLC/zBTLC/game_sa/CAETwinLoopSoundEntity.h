#pragma once

/* This class is used to control 2 sounds as one. There are 2 sounds
   created with PlayTwinLoopSound(), and one of them is playing when second
   is simply muted. When time m_dwTimeToSwapSounds is reached, these sounds
   are switched: second starts playing, first begins being muted.
   The time m_dwTimeToSwapSounds is calcualated as:
   CAEAudioUtility::GetRandomNumberInRange(m_wPlayTimeMin, m_wPlayTimeMax);
   Notice these sounds must be situated in same bank slot.
   m_pBaseAudio is a pointer to audio which created twin sound. For example,
   this could be CAEVehicleAudioEntity for playing skid sounds.              */

#include "plbase/PluginBase_SA.h"
#include "CAEAudioEntity.h"

#pragma pack(push, 1)
class CAETwinLoopSoundEntity : public CAEAudioEntity
{
	short m_wBankSlotId;
	short m_wSoundType[2];
	char pad1[2];
	CAEAudioEntity *m_pBaseAudio;
	short field_88;
	short field_8A;
	short field_8C;
	short m_wPlayTimeMin;
	short m_wPlayTimeMax;
	char pad2[2];
	unsigned int m_dwTimeToSwapSounds;
	bool m_bPlayingFirstSound;
	char pad3;
	short m_wStartingPlayPercentage[2]; // 0 - 99 percentage
	short field_9E;
	CAESound *m_apSounds[2];
};
#pragma pack(pop)

VALIDATE_SIZE(CAETwinLoopSoundEntity, 0xA8);