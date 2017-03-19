#pragma once

#include "plbase/PluginBase_SA.h"
#include "CPed.h"

class CHud
{
public:
	// static char m_BigMessage[7][128];
	static char (*m_BigMessage)[128];
	static Bool &bScriptForceDisplayWithCounters;
	
	static char &Message;

	static char* &LastZoneName;
	static char* &ZonetoPrint_glb;
	static char* &ZonetoPrint;
	static int &ZoneState;
	static int &ZoneNameTimer;
	static int &ZoneFadeTimer;

	static char* &LastVehicleName;
	static char* &VehicleName;
	static int &VehicleState;
	static int &VehicleNameTimer;
	static int &VehicleFadeTimer;

    static void SetHelpMessage(char const *text, bool quickMessage, bool permanent, bool addToBrief);

	static int Enableclock;

	static float x_fac(float x);
	static float y_fac(float y);

	static void DrawPlayerInfo();
	static void DrawPlayerhealthandarmor(CPed *player);
	static void DrawWeaponIcon();
	static void DrawWeaponAmmo();
	static void DrawWantedLevel();
	static void DrawZoneText();
	static void DrawCarName();
	static void DrawWastedArrested();

};