#pragma once

#include "plbase/PluginBase_SA.h"

#pragma pack(push, 4)
class AnimBlendFrameData
{
public:
	unsigned char m_nFlags;
	CVector m_vOffset;
	class IFrame *m_pIFrame;
	unsigned int m_dwNodeId;
};
#pragma pack(pop)

