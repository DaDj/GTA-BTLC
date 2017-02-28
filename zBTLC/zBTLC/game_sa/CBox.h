#pragma once

#include "plbase/PluginBase_SA.h"
#include "CVector.h"

#pragma pack(push, 4)
class  CBox
{
public:
	CVector m_max;
	CVector m_min;

	void Set(CVector  const& sup, CVector  const& inf);
	// updates box corners, like (if left>right then swap(left, right))
	void Recalc();
};
#pragma pack(pop)

VALIDATE_SIZE(CBox, 0x18);