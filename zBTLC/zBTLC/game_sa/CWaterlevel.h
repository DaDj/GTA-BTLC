#pragma once
#define char char
#define short short
#define int int
#define __int64 long long

/* 580 */
struct CWaterVertex
{
	short posX;
	short posY;
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
	short field_0;
	short field_2;
	short field_4;
	unsigned short field_6;
};

/* 582 */
struct CWaterQuad
{
	short field_0;
	short field_2;
	short field_4;
	short field_6;
	short m_flags;
};


class CWaterlevel
{
public:
	static CWaterVertex Vertices[2021];
	static CWaterQuad Quads[601];
	static CWaterTriangle Triangles[12];
	static short QuadsandTrianglesList[801];
};

