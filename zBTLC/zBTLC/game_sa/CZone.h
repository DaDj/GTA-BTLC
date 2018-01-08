#pragma once
#include "plbase/PluginBase_SA.h"

enum eZoneType
{
	ZONE_TYPE_DISTRICT = 0,		// controls text s
	ZONE_TYPE_ISLAND = 3
};


enum eLevelName
{
	LEVEL_NAME_COUNTRY_SIDE,
	LEVEL_NAME_LOS_SANTOS,
	LEVEL_NAME_SAN_FIERRO,
	LEVEL_NAME_LAS_VENTURAS
};

#pragma pack(push, 1)
struct CZone
{
	char name[8];
	char text[8];
	short x1;
	short y1;
	short z1;
	short x2;
	short y2;
	short z2;
	short _zoneExtraIndexInfo;
	char type;
	char townNumber;

	// Returns pointer to GXT name string.
	const char* GetTranslatedName();
};
#pragma pack(pop)