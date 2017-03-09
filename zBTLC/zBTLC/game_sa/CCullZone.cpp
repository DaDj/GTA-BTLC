#include "CCullZone.h"

char CCullZoneBase::containsPoint(float x, float y, float z)
{
	return	((char(__thiscall *)(void *, float, float, float))0x72D850)(this, x, y, z);
}


int CCullzone::Init()
{
	return	((char(__cdecl *)())0x72D6B0)();
}


void CCullzone::Update()
{
	((void(__cdecl *)())0x72DEC0)();
}




int CCullzone::getCenterPoint(int a2)
{
	return	 ((int(__thiscall *)(void *, int))0x72D6D0)(this, a2);
}


int  CCullzone::AddCullZone(CVector const& center, float zero1, float ywidth, float zbottom, float xwidth, float zero2, float ztop, int flags)
{
	return	((int(__cdecl *)(CVector const& , float , float, float , float , float, float , int ))0x72DF70)(center, zero1, ywidth, zbottom, xwidth,zero2,ztop,flags);
}


int CCullzone::AddMirrorAttributeZone(CVector const& center, float unk1, float ywidth, float zbottom, float xwidth, float unk2, float ztop, char flags, int cm, float vx, float vy, float vz)
{
	return	((int(__cdecl *)(CVector const&, float, float, float, float, float, float, char, int, float, float , float))0x72DC10)(center, unk1, ywidth, zbottom, xwidth, unk2, ztop, flags, cm, vx,vy,vz);
}

int CCullzone::AddTunnelAttributeZone(CVector const& center, float zero1, float ywidth, float zbottom, float xwidth, float zero2, float ztop, short flags)
{
	return	((int(__cdecl *)(CVector const&, float, float, float, float, float, float, short))0x72DB50)(center, zero1, ywidth, zbottom, xwidth, zero2, ztop, flags);
}


char CCullzone::Cam1stPersonForPlayer()
{
	return	((char(__cdecl *)())0x72DD40)();
}


char CCullzone::CamCloseInForPlayer()
{
	return	((char(__cdecl *)())0x72DD20)();
}

char CCullzone::CamNoRain()
{
	return	((char(__cdecl *)())0x72DDB0)();
}


char CCullzone::CamStairsForPlayer()
{
	return	((char(__cdecl *)())0x72DD30)();
}

char CCullzone::DoExtraAirResistanceForPlayer()
{
	return	((char(__cdecl *)())0x72DDD0)();
}

char CCullzone::DoINeedToLoadCollision()
{
	return	((char(__cdecl *)())0x72DDA0)();
}

char CCullzone::FewerCars()
{
	return ((char(__cdecl *)())0x72DD80)();
}

int CCullzone::FindAttributesForCoors(CVector pos)
{
	return	((int(__cdecl *)(CVector))0x72D970)(pos);
}


char CCullzone::InRoomForAudio()
{
	return	((char(__cdecl *)())0x72DD70)();
}


char CCullzone::NoPolice()
{
	return	((char(__cdecl *)())0x72DD50)();
}


char CCullzone::PlayerNoRain()
{
	return	((char(__cdecl *)())0x72DDC0)();
}

char CCullzone::PoliceAbandonCars()
{
return	((char(__cdecl *)())0x72DD60)();
}




