#pragma once

#include "plbase/PluginBase_SA.h"

#pragma pack(push, 4)
class CPedAcquaintance
{
public:
	unsigned int m_dwRespect;
	unsigned int m_dwLike;
	unsigned int field_8;
	unsigned int m_dwDislike;
	unsigned int m_dwHate;
};
#pragma pack(pop)

VALIDATE_SIZE(CPedAcquaintance, 0x14);