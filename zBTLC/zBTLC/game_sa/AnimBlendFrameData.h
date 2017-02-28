#pragma once

#include "plbase/PluginBase_SA.h"

#pragma pack(push, 4)
class AnimBlendFrameData
{
public:
	unsigned __int8 m_nFlags;
	CVector m_vOffset;
	class IFrame *m_pIFrame;
	unsigned __int32 m_dwNodeId;
};
#pragma pack(pop)

