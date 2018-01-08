#pragma once

#include "plbase/PluginBase_SA.h"

#pragma pack(push, 1)
class CColTriangle
{
public:
	unsigned short m_VertA; // vertex index in vertices array
	unsigned short m_VertB; // vertex index in vertices array
	unsigned short m_VertC; // vertex index in vertices array
	unsigned char m_nMaterial;
	unsigned char m_nLigh;
};
#pragma pack(pop)

VALIDATE_SIZE(CColTriangle, 8);