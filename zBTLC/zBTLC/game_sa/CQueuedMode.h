#pragma once

#include "plbase/PluginBase_SA.h"

#pragma pack(push, 4)
class CQueuedMode
{
public:
	unsigned short m_wMode;
	float            m_fDuration;
	unsigned short m_MinZoom;
	unsigned short m_MaxZoom;
};
#pragma pack(pop)

VALIDATE_SIZE(CQueuedMode, 0xC);