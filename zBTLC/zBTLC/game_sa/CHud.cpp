#include "CHud.h"
#include "CPed.h"
#include "CWorld.h"
#include "CFont.h"
#include "RenderWare.h"
#include "CSprite2d.h"
#include "CTimer.h"
#include "../Patch/MemoryMgr.h"
#include "../BTLC_BASE/other_shared.h"
#include "CRadar.h"
#include "CTheScripts.h"
#include "CTimer.h"
#include "CCamera.h"
#include "CSprite.h"

char(*CHud::m_BigMessage)[128] = (char(*)[128])0xBAACC0;
bool &CHud::bScriptDontDisplayAreaName = *(bool *)0xBAA3F8;
bool &CHud::bScriptDontDisplayVehicleName = *(bool *)0xBAA3F9;
bool &CHud::bScriptForceDisplayWithCounters = *(bool *)0xBAA3FA;
bool &CHud::bScriptDontDisplayRadar = *(bool *)0xBAA3FB;
int &CHud::m_LastBreathTime = *(int *)0xBAA3FC;
Bool &CHud::bDrawClock = *(Bool *)0xBAA400;
int &CHud::m_WeaponState = *(int *)0xBAA404;
int &CHud::m_WeaponFadeTimer = *(int *)0xBAA408;
int &CHud::m_WeaponTimer = *(int *)0xBAA40C;
int &CHud::m_LastWeapon = *(int *)0xBAA410;
int &CHud::m_WantedState = *(int *)0xBAA414;
int &CHud::m_WantedFadeTimer = *(int *)0xBAA418;
int &CHud::m_WantedTimer = *(int *)0xBAA41C;
int &CHud::m_LastWanted = *(int *)0xBAA420;
int &CHud::m_DisplayScoreState = *(int *)0xBAA424;
int &CHud::m_DisplayScoreFadeTimer = *(int *)0xBAA428;
int &CHud::m_DisplayScoreTimer = *(int *)0xBAA42C;
int &CHud::m_LastDisplayScore = *(int *)0xBAA430;
int &CHud::m_EnergyLostState = *(int *)0xBAA434;
int &CHud::m_EnergyLostFadeTimer = *(int *)0xBAA438;
int &CHud::m_EnergyLostTimer = *(int *)0xBAA43C;
int &CHud::m_LastTimeEnergyLost = *(int *)0xBAA440;
char* &CHud::m_VehicleName = *(char **)0xBAA458;
char* &CHud::m_LastVehicleName = *(char **)0xBAA454;
int &CHud::m_VehicleState = *(int *)0xBAA448;
int &CHud::m_VehicleNameTimer = *(int *)0xBAA450;
int &CHud::m_VehicleFadeTimer = *(int *)0xBAA44C;
bool &CHud::m_bDraw3dMarkers = *(bool *)0xBAA45C;
bool &CHud::m_Wants_To_Draw_Hud = *(bool *)0xBAA45D;
float &CHud::m_fHelpMessageTime = *(float *)0xBAA460;
float &CHud::m_fHelpMessageBoxWidth = *(float *)0x8D0934;
bool &CHud::m_bHelpMessagePermanent = *(bool *)0xBAA464;
float &CHud::m_fHelpMessageStatUpdateValue = *(float *)0xBAA468;
unsigned short &CHud::m_nHelpMessageMaxStatValue = *(unsigned short *)0xBAA46C;
unsigned short &CHud::m_nHelpMessageStatId = *(unsigned short *)0xBAA470;
bool &CHud::m_bHelpMessageQuick = *(bool *)0xBAA472;
int &CHud::m_nHelpMessageState = *(int *)0xBAA474;
int &CHud::m_nHelpMessageFadeTimer = *(int *)0xBAA478;
int &CHud::m_nHelpMessageTimer = *(int *)0xBAA47C;
char *CHud::m_pHelpMessageToPrint = (char *)0xBAA480;
char *CHud::m_pLastHelpMessage = (char *)0xBAA610;
char *CHud::m_pHelpMessage = (char *)0xBAA7A0;
char &CHud::m_Message = *(char*)0xBAB040; //wrong should be an array(this is only the first entry
char* &CHud::m_LastZoneName = *(char **)0xBAB1D4;
char* &CHud::m_ZoneName = *(char **)0xBAB1D8;
char* &CHud::m_ZonetoPrint = *(char **)0xBAB1D0;
int &CHud::m_ZoneState = *(int *)0xBAA930;
int &CHud::m_ZoneFadeTimer = *(int *)0xBAA934;
int &CHud::m_ZoneNameTimer = *(int *)0xBAA938;
short &CHud::m_ItemToFlash = *(short *)0xBAB1DC;
bool &CHud::bDrawingVitalStats = *(bool *)0xBAB1DE;
CSprite2d *CHud::Sprites = (CSprite2d *)0xBAB1FC;

short &TimerMainCounterHideState = *(short *)0xBAA388;
bool &TimerMainCounterWasDisplayed = *(bool *)0xBAA38A;
short *TimerCounterHideState = (short *)0xBAA38C;
short *TimerCounterWasDisplayed = (short *)0xBAA394;
int &OddJob2OffTimer = *(int *)0xBAA398;
float &OddJob2XOffset = *(float *)0xBAA39C;
int &OddJob2Timer = *(int *)0xBAA3A0;
float *BigMessageAlpha = (float *)0xBAA3A4;
float *BigMessageInUse = (float *)0xBAA3C0;
float *BigMessageX = (float *)0xBAA3DC;
char *LastBigMessage = (char *)0xBAABC0;
unsigned short &OddJob2On = *(unsigned short *)0xBAB1E0;
float &PagerXOffset = *(float *)0x8D0938;


void CHud::SetHelpMessage(char const *text, bool quickMessage, bool permanent, bool addToBrief) 
{
    ((void(__cdecl *)(char const *, bool, bool, bool))0x588BE0)(text, quickMessage, permanent, addToBrief);
}

float CHud::x_fac(float x)
{
	float width_fac = RsGlobal.maximumWidth / 640.0f;
	return x * width_fac;
}


float CHud::y_fac(float y)
{
	float height_fac = RsGlobal.maximumHeight / 448.0f;
	return y * height_fac;
}

void CHud::DrawPlayerInfo()
{
	CPed *player = CWorld::Players[CWorld::PlayerInFocus].m_pPed;
	char string[40];

	CFont::SetColor(CRGBA::CRGBA(200,200,200,255));
	sprintf(string, "FPS : %d", (int)CTimer::ms_gameFPS);
	CFont::SetFontStyle(FONT_PRICEDOWN);
	CFont::SetAlignment(ALIGN_CENTER);
	CFont::SetOutlinePosition(1);
	CFont::SetScale(CHud::x_fac(0.3f), CHud::y_fac(0.45f));
	CFont::PrintString(CHud::x_fac(540.0f),CHud::y_fac(10.0f), string);

	CHud::DrawPlayerhealthandarmor(player);
}

void CHud::DrawPlayerhealthandarmor(CPed *player)
{
	static unsigned int lastdamagetaken;

	float percentage_health = (player->m_fHealth / player->m_fMaxHealth) * 100;
	CRGBA color_health = CRGBA::CRGBA(10, 110, 10, 255);
	if (percentage_health < 30)
		color_health = CRGBA::CRGBA(90, 0, 0, 255);

	float percentage_armor = player->m_fArmour ;
	CRGBA color_armor = CRGBA::CRGBA(200, 200, 230, 245);
	if(percentage_armor <= 1.0f)
	      color_armor = CRGBA::CRGBA(200, 200, 230, 90);

	lastdamagetaken = CWorld::Players[CWorld::PlayerInFocus].m_dwLastTimeEnergyLost;
	//CSprite2d::DrawRect(CRect::CRect(CHud::x_fac(29.0f), CHud::y_fac(400.0f), CHud::x_fac(99.0f), CHud::y_fac(455.0f + 8.0)), CRGBA::CRGBA(30, 30, 30, 180));
	if (CTimer::m_snTimeInMilliseconds < (lastdamagetaken + 100))
	{
		CSprite2d::DrawRect(CRect::CRect(CHud::x_fac(0.0f), CHud::y_fac(0.0f), CHud::x_fac(640.0f), CHud::y_fac(448.0f)), CRGBA::CRGBA(80, 30, 30, 40));
	}

	if (!KeyPressed(VK_TAB))
	{
		CSprite2d::DrawRect(CRect::CRect(CHud::x_fac(10.0f), CHud::y_fac(448.0f-21.0f), CHud::x_fac(99.0f), CHud::y_fac(448.0f - 4.0f)), CRGBA::CRGBA(50, 50, 50, 190));
		CSprite2d::DrawBarChart(CHud::x_fac(11.0f), CHud::y_fac(448.0f - 20.0f), CHud::x_fac(87.0f), CHud::y_fac(7.0f), percentage_health, 0, 0, 0, color_health, color_health);
		//CSprite2d::DrawRect(CRect::CRect(CHud::x_fac(20.0), CHud::y_fac(464.0f), CHud::x_fac(98.0f), CHud::y_fac(465.0f + 8.0f)), CRGBA::CRGBA(30, 30, 30, 180));
		CSprite2d::DrawBarChart(CHud::x_fac(11.0f), CHud::y_fac(448.0f - 12.0f), CHud::x_fac(87.0f), CHud::y_fac(7.0f), percentage_armor, 0, 0, 0, color_armor, color_armor);
	}
}

void CHud::DrawWeaponIcon()
{

}

void CHud::DrawWeaponAmmo()
{

}

void CHud::DrawWantedLevel()
{

}

void CHud::DrawZoneText()
{

	float Fontalpha = 255.0;
	if (m_ZoneName)
	{
		if (m_ZoneName != m_LastZoneName)
		{
			switch (m_ZoneState)
			{
			case 0:
				if (!CTheScripts::PlayerisOffMap && CTheScripts::DisplayHud )
				{
					m_ZoneState = 2;
					m_ZoneNameTimer = 0;
					m_ZoneFadeTimer = 0;
					m_ZonetoPrint = m_ZoneName;
				/*	if (m_VehicleState == 2 || m_VehicleState == 1)
						m_VehicleState = 3;*/
				}
				break;
			case 1:
			case 2:
			case 3:
				m_ZoneState = 4;
			case 4:
				m_ZoneNameTimer = 0;
				break;
			default:
				break;
			}
		}
		m_LastZoneName = m_ZonetoPrint;

	}



	if (m_ZoneState)
	{
		switch (m_ZoneState)
		{
		case 1:
			Fontalpha = 255.0;
			m_ZoneFadeTimer = 1000;
			if (m_ZoneNameTimer > 3000.0)
				m_ZoneState = 3;
			break;
		case 2:
			if (!TheCamera.GetFading() && TheCamera.GetFadeStage() != 2)
				m_ZoneFadeTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
			if (m_ZoneFadeTimer > 1000.0)
			{
				m_ZoneFadeTimer = 1000;
				m_ZoneState = 1;
			}
			if (TheCamera.GetFadeStage() != 2)
			{
				Fontalpha = m_ZoneFadeTimer * 0.001 * 255.0;
				break;
			}
			Fontalpha = 255.0;
			m_ZoneState = 3;
			m_ZoneFadeTimer = 1000;
			break;
		case 3:
			if (!TheCamera.GetFading() && TheCamera.GetFadeStage() != 2)
				m_ZoneFadeTimer += CTimer::ms_fTimeStep * 0.02 * -1000.0;
			if (m_ZoneFadeTimer < 0.0)
			{
				m_ZoneFadeTimer = 0;
				m_ZoneState = 0;
			}
			if (TheCamera.GetFadeStage() != 2)
			{
				Fontalpha = m_ZoneFadeTimer * 0.001 * 255.0;
				break;
			}
			m_ZoneFadeTimer = 1000;
			Fontalpha = 255.0;
			break;
		case 4:
			m_ZoneFadeTimer += CTimer::ms_fTimeStep * 0.02 * -1000.0;
			if (m_ZoneFadeTimer < 0.0)
			{
				m_ZoneFadeTimer = 0;
				m_ZoneState = 2;
				m_ZonetoPrint = m_ZoneName;
			}
			Fontalpha = m_ZoneFadeTimer * 0.001 * 255.0;
			break;
		default:
			break;
		}

		float &unknownA = *(float*)0xBAA3E0;
		float &unknownB = *(float*)0xBAA3E4;


		if (m_Message ||  unknownA != 0.0f || unknownB != 0.0)
		{
			m_ZoneState = 3;
		}
		else
		{
			CHud::m_ZoneNameTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
			CFont::SetAlignment(ALIGN_RIGHT);
			CFont::SetProp(true);
			CFont::SetBackground(false,false);
			CFont::SetScale(x_fac(0.3f), y_fac(0.6f));
			CFont::SetOutlinePosition(1);
			CFont::SetDropColor(CRGBA::CRGBA(30, 30, 30, Fontalpha));
			CFont::SetFontStyle(2);
			CFont::SetColor(CRGBA::CRGBA(180, 180, 180, Fontalpha));
			CFont::PrintStringFromBottom(x_fac(640.0 - 32.0), y_fac(448.0 - 20.0), m_ZoneName);

		}
	}

	
}

void CHud::DrawCarName()
{
	float Fontalpha = 255.0;
	if (m_VehicleName)
	{
		if (m_VehicleName != m_LastVehicleName)
		{
			if (m_VehicleState)
			{
				if (m_VehicleState > 0 && m_VehicleState <= 4)
				{
					m_VehicleState = 4;
					m_VehicleNameTimer = 0;
				}
			}
			else
			{
				m_VehicleState = 2;
				m_VehicleNameTimer = 0;
				m_VehicleFadeTimer = 0;
				/*if (ZoneState == 1 || ZoneState == 2)
					ZoneState = 3;*/
			}
			m_LastVehicleName = m_VehicleName;
		}


		if (m_VehicleState)
		{
			switch (m_VehicleState)
			{
			case 2:
				m_VehicleFadeTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
				if (m_VehicleFadeTimer > 1000.0)
				{
					m_VehicleFadeTimer = 1000;
					m_VehicleState = 1;
				}
				Fontalpha = m_VehicleFadeTimer * 0.001 * 255.0;
				break;
			case 3:
				m_VehicleFadeTimer += CTimer::ms_fTimeStep * 0.02 * -1000.0;
				if (m_VehicleFadeTimer >= 0)
				{
					Fontalpha = m_VehicleFadeTimer * 0.001 * 255.0;
					break;
				}
				m_VehicleState = 0;
				m_VehicleFadeTimer = 0;
				Fontalpha = m_VehicleFadeTimer * 0.001 * 255.0;
				break;
			case 4:
				m_VehicleFadeTimer += CTimer::ms_fTimeStep * 0.02 * -1000.0;
				if (m_VehicleFadeTimer < 0)
				{
					m_VehicleNameTimer = 0;
					m_VehicleState = 2;
					m_VehicleFadeTimer = 0;
				}
				Fontalpha = m_VehicleFadeTimer * 0.001 * 255.0;
				break;
			case 1:
				if (m_VehicleNameTimer > 3000.0)
				{
					m_VehicleState = 3;
					m_VehicleFadeTimer = 1000;
				}
				Fontalpha = 255.0;
				break;
			default:
				break;
			}


			if (!m_Message && CTheScripts::DisplayHud)
			{
				m_VehicleNameTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
				CFont::SetAlignment(ALIGN_RIGHT);
				CFont::SetProp(true);
				CFont::SetBackground(false, false);
				CFont::SetScale(x_fac(0.3f), y_fac(0.6f));
				CFont::SetOutlinePosition(1);
				CFont::SetDropColor(CRGBA::CRGBA(30, 30, 30,max(Fontalpha -50.0,0.0f)));
				CFont::SetFontStyle(2);
				CFont::SetColor(CRGBA::CRGBA(140, 145, 140, Fontalpha));
				CFont::PrintString(x_fac(640.0 - 32.0), y_fac(448.0 - 45.0), m_VehicleName);
			}
		}
	}

	else
	{
		m_VehicleState = 0;
		m_VehicleNameTimer = 0;
		m_VehicleFadeTimer = 0;
		m_LastVehicleName = 0;
	}
}

void CHud::DrawWastedArrested()
{

}
