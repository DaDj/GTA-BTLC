#pragma once
#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long

/* 580 */
struct CWaterVertex
{
	__int16 posX;
	__int16 posY;
	float posZ;
	int tU;
	int tV;
	char field_10;
	char field_11;
	char pad_12;
	char field_13;
};

/* 581 */
struct CWaterTriangle
{
	__int16 field_0;
	__int16 field_2;
	__int16 field_4;
	unsigned __int16 field_6;
};

/* 582 */
struct CWaterQuad
{
	__int16 field_0;
	__int16 field_2;
	__int16 field_4;
	__int16 field_6;
	__int16 m_flags;
};


class CWaterlevel
{
public:
	static CWaterVertex Vertices[2021];
	static CWaterQuad Quads[601];
	static CWaterTriangle Triangles[12];
	static __int16 QuadsandTrianglesList[801];
};

