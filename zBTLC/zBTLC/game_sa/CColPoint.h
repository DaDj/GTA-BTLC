#pragma once

#include "plbase/PluginBase_SA.h"
#include "CVector.h"


struct tColLighting {
	union {
		struct {
			uint8 day : 4;
			uint8 night : 4;
		};
		uint8 value;
	};
};

#pragma pack(push, 4)
class CColPoint
{
public:
	/* https://code.google.com/p/mtasa-blue/source/browse/tags/1.3.4/MTA10/game_sa/CColPointSA.h */
	CVector         m_vPoint;
	float field_C;
	CVector         m_vNormal;
	float field_1C;
	unsigned char m_nSurfaceTypeA;
	unsigned char m_nPieceTypeA;
	unsigned char m_nLightingA;
	unsigned char m_nSurfaceTypeB;
	unsigned char m_nPieceTypeB;
	unsigned char m_nLightingB;
	float           m_fDepth;

	void operator=(CColPoint const& right);
};
#pragma pack(pop)

VALIDATE_SIZE(CColPoint, 0x2C);