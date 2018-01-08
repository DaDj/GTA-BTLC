#pragma once

#include "plbase/PluginBase_SA.h"

#pragma pack(push, 4)
class CClothes
{
public:
	unsigned int m_adwModelKeys[10];
	unsigned int m_adwTextureKeys[18];
	float m_fFatStat;
	float m_fMuscleStat;
};
#pragma pack(pop)

VALIDATE_SIZE(CClothes, 0x78);