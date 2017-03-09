#pragma once
#include "plbase/PluginBase_SA.h"
#include "CVector.h"


struct CCullZoneBase
{
	short x;
	short y;
	short field_4;
	short Ywidth;
	short Xwidth;
	short field_A;
	short Zbottom;
	short Ztop;

	char containsPoint(float x, float y, float z);
};


class CCullZoneReflection
{
public:
	CCullZoneBase __parent;
	float cm;
	char vx;
	char vy;
	char vz;
	char flags;
};




class CCullzone
{
public:
	CCullZoneBase __parent;
	short flags;

	int getCenterPoint(int a2);
	int AddCullZone(CVector const& center , float zero1, float ywidth, float zbottom, float xwidth, float zero2, float ztop, int flags);
	int AddMirrorAttributeZone(CVector const& center, float unk1, float ywidth, float zbottom, float xwidth, float unk2, float ztop, char flags, int cm, float vx, float vy, float vz);
	int AddTunnelAttributeZone(CVector const& center, float zero1, float ywidth, float zbottom, float xwidth, float zero2, float ztop, short flags);
	static char Cam1stPersonForPlayer();
	static char CamCloseInForPlayer();
	static char CamNoRain();
	static char CamStairsForPlayer();
	static char DoExtraAirResistanceForPlayer();
	static char DoINeedToLoadCollision();
	static char FewerCars();
	static int	FindAttributesForCoors(CVector pos);
	static char InRoomForAudio();
	static int Init();
	static char NoPolice();
	static char PlayerNoRain();
	static char PoliceAbandonCars();
	static void Update();
};

