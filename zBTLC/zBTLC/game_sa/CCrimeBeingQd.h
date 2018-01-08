#pragma once

#include "plbase/PluginBase_SA.h"
#include "CVector.h"

#pragma pack(push, 4)
class CCrimeBeingQd
{
public:
    unsigned int m_dwCrimeType;
    unsigned int m_dwCrimeId;
    unsigned int m_dwStartTime;
    CVector m_vCoors;
    unsigned char m_bAlreadyReported;
    unsigned char m_bPoliceDontReallyCare;
};
#pragma pack(pop)

VALIDATE_SIZE(CCrimeBeingQd, 0x1C);