#pragma once

#include "plbase/PluginBase_SA.h"
#include "CAEAudioEntity.h"
#include "CAESound.h"

#pragma pack(push, 1)
class CPedVoice : public CAEAudioEntity
{
public:
	char field_7C[20];
	char field_90;
	char field_91;
	short m_wVoiceType;
	short m_wVoiceID;
	short m_wVoiceGender;
	char field_98;
	char m_bEnableVocalType;
	char m_bMuted;
	char m_nVocalEnableFlag;
	char field_9C;
	char field_9D;
	char field_9E;
	char field_9F;
	CAESound *m_pSound;
	short field_A4;
	short field_A6;
	short field_A8;
	short field_AA;
	float m_fVoiceVolume1;
	short m_wVoiceVolume2;
	short field_B2;
	int field_B4[19];
};
#pragma pack(pop)

VALIDATE_SIZE(CPedVoice, 0x100);