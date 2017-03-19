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

char (*CHud::m_BigMessage)[128] = (char (*)[128])0xBAACC0;
Bool &CHud::bScriptForceDisplayWithCounters = *(Bool *)0xBAA3FA;

char &CHud::Message = *(char*)0xBAB040; //wrong should be an array(this is only the first entry
char* &CHud::LastZoneName = *(char **)0xBAB1D4;
char* &CHud::ZonetoPrint_glb = *(char **)0xBAB1D8;
char* &CHud::ZonetoPrint = *(char **)0xBAB1D0;
int &CHud::ZoneState = *(int *)0xBAA930;
int &CHud::ZoneFadeTimer = *(int *)0xBAA934;
int &CHud::ZoneNameTimer = *(int *)0xBAA938;

char* &CHud::VehicleName = *(char **)0xBAA458;
char* &CHud::LastVehicleName = *(char **)0xBAA454;
int &CHud::VehicleState = *(int *)0xBAA448;
int &CHud::VehicleNameTimer = *(int *)0xBAA450;
int &CHud::VehicleFadeTimer = *(int *)0xBAA44C;

void CHud::SetHelpMessage(char const *text, bool quickMessage, bool permanent, bool addToBrief) {
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
		CSprite2d::DrawRect(CRect::CRect(CHud::x_fac(0.0f), CHud::y_fac(0.0f), CHud::x_fac(640.0f), CHud::y_fac(448.0f)), CRGBA::CRGBA(30, 30, 30, 40));
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
	if (ZonetoPrint_glb)
	{
		if (ZonetoPrint_glb != LastZoneName)
		{
			switch (ZoneState)
			{
			case 0:
				if (!CTheScripts::PlayerisOffMap && CTheScripts::DisplayHud )
				{
					ZoneState = 2;
					ZoneNameTimer = 0;
					ZoneFadeTimer = 0;
					ZonetoPrint = ZonetoPrint_glb;
				/*	if (VehicleState == 2 || VehicleState == 1)
						VehicleState = 3;*/
				}
				break;
			case 1:
			case 2:
			case 3:
				ZoneState = 4;
			case 4:
				ZoneNameTimer = 0;
				break;
			default:
				break;
			}
		}
		LastZoneName = ZonetoPrint;

	}



	if (ZoneState)
	{
		switch (ZoneState)
		{
		case 1:
			Fontalpha = 255.0;
			ZoneFadeTimer = 1000;
			if (ZoneNameTimer > 3000.0)
				ZoneState = 3;
			break;
		case 2:
			if (!TheCamera.GetFading() && TheCamera.GetFadeStage() != 2)
				ZoneFadeTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
			if (ZoneFadeTimer > 1000.0)
			{
				ZoneFadeTimer = 1000;
				ZoneState = 1;
			}
			if (TheCamera.GetFadeStage() != 2)
			{
				Fontalpha = ZoneFadeTimer * 0.001 * 255.0;
				break;
			}
			Fontalpha = 255.0;
			CHud::ZoneState = 3;
			CHud::ZoneFadeTimer = 1000;
			break;
		case 3:
			if (!TheCamera.GetFading() && TheCamera.GetFadeStage() != 2)
				ZoneFadeTimer += CTimer::ms_fTimeStep * 0.02 * -1000.0;
			if (ZoneFadeTimer < 0.0)
			{
				ZoneFadeTimer = 0;
				ZoneState = 0;
			}
			if (TheCamera.GetFadeStage() != 2)
			{
				Fontalpha = ZoneFadeTimer * 0.001 * 255.0;
				break;
			}
			ZoneFadeTimer = 1000;
			Fontalpha = 255.0;
			break;
		case 4:
			ZoneFadeTimer += CTimer::ms_fTimeStep * 0.02 * -1000.0;
			if (ZoneFadeTimer < 0.0)
			{
				ZoneFadeTimer = 0;
				ZoneState = 2;
				ZonetoPrint = ZonetoPrint_glb;
			}
			Fontalpha = ZoneFadeTimer * 0.001 * 255.0;
			break;
		default:
			break;
		}

		float &unknownA = *(float*)0xBAA3E0;
		float &unknownB = *(float*)0xBAA3E4;


		if (Message ||  unknownA != 0.0f || unknownB != 0.0)
		{
			ZoneState = 3;
		}
		else
		{
			CHud::ZoneNameTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
			CFont::SetAlignment(ALIGN_RIGHT);
			CFont::SetProp(true);
			CFont::SetBackground(false,false);
			CFont::SetScale(x_fac(0.3f), y_fac(0.6f));
			CFont::SetOutlinePosition(1);
			CFont::SetDropColor(CRGBA::CRGBA(30, 30, 30, Fontalpha));
			CFont::SetFontStyle(2);
			CFont::SetColor(CRGBA::CRGBA(180, 180, 180, Fontalpha));
			CFont::PrintStringFromBottom(x_fac(640.0 - 32.0), y_fac(448.0 - 20.0), ZonetoPrint_glb);

		}
	}

	
}

void CHud::DrawCarName()
{
	float Fontalpha = 255.0;
	if (VehicleName)
	{
		if (VehicleName != LastVehicleName)
		{
			if (VehicleState)
			{
				if (VehicleState > 0 && VehicleState <= 4)
				{
					VehicleState = 4;
					VehicleNameTimer = 0;
				}
			}
			else
			{
				VehicleState = 2;
				VehicleNameTimer = 0;
				VehicleFadeTimer = 0;
				/*if (ZoneState == 1 || ZoneState == 2)
					ZoneState = 3;*/
			}
			LastVehicleName = VehicleName;
		}


		if (VehicleState)
		{
			switch (VehicleState)
			{
			case 2:
				VehicleFadeTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
				if (VehicleFadeTimer > 1000.0)
				{
					VehicleFadeTimer = 1000;
					VehicleState = 1;
				}
				Fontalpha = VehicleFadeTimer * 0.001 * 255.0;
				break;
			case 3:
				VehicleFadeTimer += CTimer::ms_fTimeStep * 0.02 * -1000.0;
				if (VehicleFadeTimer >= 0)
				{
					Fontalpha = VehicleFadeTimer * 0.001 * 255.0;
					break;
				}
				VehicleState = 0;
				VehicleFadeTimer = 0;
				Fontalpha = VehicleFadeTimer * 0.001 * 255.0;
				break;
			case 4:
				VehicleFadeTimer += CTimer::ms_fTimeStep * 0.02 * -1000.0;
				if (VehicleFadeTimer < 0)
				{
					VehicleNameTimer = 0;
					VehicleState = 2;
					VehicleFadeTimer = 0;
				}
				Fontalpha = VehicleFadeTimer * 0.001 * 255.0;
				break;
			case 1:
				if (VehicleNameTimer > 3000.0)
				{
					VehicleState = 3;
					VehicleFadeTimer = 1000;
				}
				Fontalpha = 255.0;
				break;
			default:
				break;
			}


			if (!Message && CTheScripts::DisplayHud)
			{
				VehicleNameTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
				CFont::SetAlignment(ALIGN_RIGHT);
				CFont::SetProp(true);
				CFont::SetBackground(false, false);
				CFont::SetScale(x_fac(0.3f), y_fac(0.6f));
				CFont::SetOutlinePosition(1);
				CFont::SetDropColor(CRGBA::CRGBA(30, 30, 30,max(Fontalpha -50.0,0.0f)));
				CFont::SetFontStyle(2);
				CFont::SetColor(CRGBA::CRGBA(140, 145, 140, Fontalpha));
				CFont::PrintString(x_fac(640.0 - 32.0), y_fac(448.0 - 45.0), VehicleName);
			}
		}
	}

	else
	{
		VehicleState = 0;
		VehicleNameTimer = 0;
		VehicleFadeTimer = 0;
		LastVehicleName = 0;
	}
}

void CHud::DrawWastedArrested()
{

}
