#pragma once

#include "plbase/PluginBase_SA.h"
#include "RenderWare.h"

#pragma pack (push, 1)
class  CTexDictionary
{
public:
	// class variables
	RwTexDictionary *m_pRwDictionary;
	unsigned short m_dwRefsCount;
	short m_dwParentIndex;
	unsigned int hash;
};
#pragma pack (pop)

VALIDATE_SIZE(CTexDictionary, 0xC);