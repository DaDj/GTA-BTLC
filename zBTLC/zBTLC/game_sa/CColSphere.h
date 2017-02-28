#pragma once

#include "plbase/PluginBase_SA.h"
#include "CSphere.h"

#pragma pack(push, 1)
class CColSphere : public CSphere
{
public:
	unsigned __int8 m_nMaterial;
	unsigned __int8 m_nFlags;
	unsigned __int8 m_nLighting;
	unsigned __int8 m_nLight;

	void Set(float radius, CVector  const& center, unsigned char material , unsigned char flags, unsigned char lighting);
	bool IntersectRay(CVector  const& rayStart, CVector  const& rayEnd, CVector& intPoint1, CVector& intPoint2);
};
#pragma pack(pop)

VALIDATE_SIZE(CColSphere, 0x14);