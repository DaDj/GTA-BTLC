#pragma once

#include "plbase/PluginBase_SA.h"
#include "CPed.h"
#include "CSprite2d.h"

enum eHudSprites {
	HUDSPRITE_FIST,
	HUDSPRITE_SITEM16,
	HUDSPRITE_SITEROCKET,
	HUDSPRITE_RADARDISC,
	HUDSPRITE_RADARRINGPLANE,
	HUDSPRITE_SKIPICON
};

class CHud
{
public:
	// static char m_BigMessage[7][128];
	static char(*m_BigMessage)[128]; // static char m_BigMessage[7][128]
	static bool &bScriptDontDisplayAreaName;
	static bool &bScriptDontDisplayVehicleName;
	static bool &bScriptForceDisplayWithCounters;
	static bool &bScriptDontDisplayRadar;
	static int &m_LastBreathTime;
	static bool &bDrawClock;
	static int &m_WeaponState;
	static int &m_WeaponFadeTimer;
	static int &m_WeaponTimer;
	static int &m_LastWeapon;
	static int &m_WantedState;
	static int &m_WantedFadeTimer;
	static int &m_WantedTimer;
	static int &m_LastWanted;
	static int &m_DisplayScoreState;
	static int &m_DisplayScoreFadeTimer;
	static int &m_DisplayScoreTimer;
	static int &m_LastDisplayScore;
	static int &m_EnergyLostState;
	static int &m_EnergyLostFadeTimer;
	static int &m_EnergyLostTimer;
	static int &m_LastTimeEnergyLost;
	static char* &m_LastVehicleName;
	static char* &m_VehicleName;
	static int &m_VehicleState;
	static int &m_VehicleNameTimer;
	static int &m_VehicleFadeTimer;
	static bool &m_bDraw3dMarkers;
	static bool &m_Wants_To_Draw_Hud;
	static float &m_fHelpMessageTime; // in seconds
	static float &m_fHelpMessageBoxWidth; // default 200.0
	static bool &m_bHelpMessagePermanent;
	static float &m_fHelpMessageStatUpdateValue;
	static unsigned short &m_nHelpMessageMaxStatValue;
	static unsigned short &m_nHelpMessageStatId;
	static bool &m_bHelpMessageQuick;
	static int &m_nHelpMessageState;
	static int &m_nHelpMessageFadeTimer;
	static int &m_nHelpMessageTimer;
	static char *m_pHelpMessageToPrint; // static char m_pHelpMessageToPrint[400]
	static char *m_pLastHelpMessage; // static char m_pLastHelpMessage[400]
	static char *m_pHelpMessage; // static char m_pHelpMessage[400]
	static char &m_Message;
	static char* &m_LastZoneName;
	static char* &m_ZoneName;
	static char* &m_ZonetoPrint;
	static int &m_ZoneState;
	static int &m_ZoneNameTimer;
	static int &m_ZoneFadeTimer;
	static short &m_ItemToFlash; // -1 - no item
	static bool &bDrawingVitalStats;
	static CSprite2d *Sprites; // static CSprite2d Sprites[6]

	static CSprite2d NewRadarSprites[2]; // static CSprite2d Sprites[6]

	static char *CHud::Spritenames[6];
	static	char *CHud::NewSpritesNames[5];
	static float Health_Radius;
	static float Health_PosX;
	static float Health_PosY;
	static float Health_innerRadius;


	static void My_Init();

	static void SetHelpMessage(char const *text, bool quickMessage, bool permanent, bool addToBrief);
	static int Enableclock;

	static float x_fac(float x);
	static float y_fac(float y);

	static void DrawPlayerInfo();
	static void DrawPlayerhealthandarmor(CPed *player);
	static void DrawWeaponInfo(CPed * player, float y_off);
	static void DrawWeaponIcon(CPed *player, float alpha, float y_off);
	static void DrawWeaponAmmo(CPed *player, float alpha, float y_off);
	static void DrawWantedLevel(CPed *player);
	static float DrawMoneyInfo(CPed * player);
	static void DrawZoneText();
	static void DrawCarName();
	static void DrawWastedArrested();
	static void DrawRadar();

	static void Initialise();
	static void ReInitialise();
	static void Shutdown();


};

extern short &TimerMainCounterHideState;
extern bool &TimerMainCounterWasDisplayed;
extern short *TimerCounterHideState;  // short TimerCounterHideState[4]
extern short *TimerCounterWasDisplayed;  // short TimerCounterWasDisplayed[4]
extern int &OddJob2OffTimer;
extern float &OddJob2XOffset;
extern int &OddJob2Timer;
extern float *BigMessageAlpha;  // float BigMessageAlpha[7]
extern float *BigMessageInUse;  // float BigMessageInUse[7]
extern float *BigMessageX;  // float BigMessageX[7]
extern char *LastBigMessage;  // char LastBigMessage[256]
extern unsigned short &OddJob2On;
extern float &PagerXOffset; // default 150.0