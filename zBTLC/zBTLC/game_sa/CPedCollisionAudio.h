#pragma once

#include "plbase/PluginBase_SA.h"
#include "CAEAudioEntity.h"
#include "CAESound.h"

#pragma pack(push, 1)
class CPedCollisionAudio : public CAEAudioEntity
{
public:
  char field_7C;
  char field_7D;
  short field_7E;
  int field_80;
  float field_84;
  float field_88;
  char field_8C[8];
  class CPed *m_pPed;
  char field_98;
  char field_99[3];
  CAESound *field_9C;
  int field_A0;
  CAESound *field_A4;
  char m_85F438[0xA8];
  CAESound *field_150;
  float field_154;
  float field_158;
};
#pragma pack(pop)

VALIDATE_SIZE(CPedCollisionAudio, 0x15C);