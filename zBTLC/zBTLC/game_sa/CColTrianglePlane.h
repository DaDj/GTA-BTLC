#pragma once

#include "plbase/PluginBase_SA.h"
#include "CompressedVector.h"
#include "CVector.h"
#include "CColTriangle.h"

#pragma pack(push, 4)
class CColTrianglePlane
{
public:
	CompressedVector m_Normal;
	unsigned short m_wDistance;
	unsigned char m_nOrientation;
	
	void GetNormal(CVector &out);
	void Set(CompressedVector  const* vertices, CColTriangle & triangle);
};
#pragma pack(pop)

VALIDATE_SIZE(CColTrianglePlane, 0xA);