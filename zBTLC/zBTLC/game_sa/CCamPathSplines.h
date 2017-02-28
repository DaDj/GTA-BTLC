#pragma once

#include "plbase/PluginBase_SA.h"

#pragma pack(push, 4)
class CCamPathSplines
{
public:
	float *m_pArrPathData;
};
#pragma pack(pop)

VALIDATE_SIZE(CCamPathSplines, 4);