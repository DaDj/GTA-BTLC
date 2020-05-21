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
#include "CBaseModelInfo.h"
#include "CWeaponInfo.h"
#include "CModelInfo.h"
#include "CTxdStore.h"
#include "common.h"
#include "CKeyGen.h"
#include "CTask.h"
#include "CCamera.h"
#include "CMenuManager.h"
#include "CPlayerPed.h"

char(*CHud::m_BigMessage)[128] = (char(*)[128])0xBAACC0;
bool &CHud::bScriptDontDisplayAreaName = *(bool *)0xBAA3F8;
bool &CHud::bScriptDontDisplayVehicleName = *(bool *)0xBAA3F9;
bool &CHud::bScriptForceDisplayWithCounters = *(bool *)0xBAA3FA;
bool &CHud::bScriptDontDisplayRadar = *(bool *)0xBAA3FB;
int &CHud::m_LastBreathTime = *(int *)0xBAA3FC;
bool &CHud::bDrawClock = *(bool *)0xBAA400;
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
CSprite2d CHud::NewRadarSprites[2]; // static CSprite2d Sprites[6]

float CHud::Health_Radius = 43.0f;
float CHud::Health_innerRadius = 38.5f;
float CHud::Health_PosX = 90.0f;
float CHud::Health_PosY = 65.0f;

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

char *CHud::Spritenames[6] = {
   "fist",
   "siteM16",
   "siterocket",
   "radardisc",
   "radarRingPlane",
   "SkipIcon",
};

char *CHud::NewSpritesNames[5] = {
  "radarringfront",
   "radarringback",
  "mp_higher",
  "mp_level",
  "mp_lower",
};


enum eHudState
{
	STATE_OFF,
	STATE_FADE_ON,
	STATE_ON,
	STATE_FADE_OFF
};

void CHud::My_Init()
{
	MemoryVP::InjectHook(0x58FBD6, &CHud::DrawPlayerInfo, PATCH_CALL);
	MemoryVP::InjectHook(0x58FBDB, &CHud::DrawWantedLevel, PATCH_CALL);
	MemoryVP::InjectHook(0x58AA50, &CHud::DrawZoneText, PATCH_JUMP);
	MemoryVP::InjectHook(0x58AEA0, &CHud::DrawCarName, PATCH_JUMP);
	MemoryVP::InjectHook(0x5BD76F, &CHud::Initialise, PATCH_CALL);
	MemoryVP::InjectHook(0x53BBA2, &CHud::Shutdown, PATCH_CALL);
	MemoryVP::InjectHook(0x58FC53, &CHud::DrawRadar, PATCH_CALL);
	MemoryVP::InjectHook(0x58FBBF, &CHud::DrawCrosshairs, PATCH_CALL);
}

void CHud::SetHelpMessage(char const *text, bool quickMessage, bool permanent, bool addToBrief)
{
	((void(__cdecl *)(char const *, bool, bool, bool))0x588BE0)(text, quickMessage, permanent, addToBrief);
}

float CHud::x_fac(float x)
{
	float width_fac = RsGlobal.maximumHeight / 448.0f;
	return x * width_fac;

	//float base = RsGlobal.maximumWidth > RsGlobal.maximumHeight ? RsGlobal.maximumHeight : RsGlobal.maximumWidth;
	//return static_cast<int>(x * base / 1080.0f);
}

float CHud::y_fac(float y)
{
	float height_fac = RsGlobal.maximumHeight / 448.0f;
	return y * height_fac;

	//float base = RsGlobal.maximumWidth > RsGlobal.maximumHeight ? RsGlobal.maximumHeight : RsGlobal.maximumWidth;
	//return static_cast<int>(y * base / 1080.0f);
}

void CHud::DrawPlayerInfo()
{
	//RADAR TESTURE
	float scaleRadius = Health_Radius + 1.5;
	CRect Icon = CRect(x_fac(Health_PosX - scaleRadius), y_fac(448 - Health_PosY + scaleRadius), x_fac(Health_PosX + scaleRadius), y_fac(448 - Health_PosY - scaleRadius));
	CHud::Sprites[3].Draw(Icon, CRGBA(255, 255, 255, 180));

	CPed *player = CWorld::Players[CWorld::PlayerInFocus].m_pPed;

	float moneypos = CHud::DrawMoneyInfo(player);
	CHud::DrawPlayerhealthandarmor(player);
	CHud::DrawWeaponInfo(player, moneypos);
}

void CHud::DrawPlayerhealthandarmor(CPed *player)
{
	static unsigned int lastdamagetaken;
	static int LastHealth;
	enum eBlinkstate
	{
		NO_BLINK,
		BLINK_ON,
		BLINK_OFF
	};

	float percentage_health = (player->m_fHealth / player->m_fMaxHealth) * 100;
	CRGBA color_health = CRGBA::CRGBA(87, 124, 88, 255);
	if (percentage_health < 30)
		color_health = CRGBA::CRGBA(90, 0, 0, 255);

	float percentage_armor = player->m_fArmour;
	CRGBA color_armor = CRGBA::CRGBA(74, 148, 160, 255);
	if (percentage_armor <= 1.0f)
		color_armor = CRGBA::CRGBA(200, 200, 230, 90);

	m_LastTimeEnergyLost = CWorld::Players[CWorld::PlayerInFocus].m_dwLastTimeEnergyLost;

	if (CTimer::m_snTimeInMilliseconds < (m_LastTimeEnergyLost + 60))
	{
		CSprite2d::DrawRect(CRect::CRect(x_fac(0.0f), y_fac(0.0f), RsGlobal.maximumWidth, RsGlobal.maximumHeight), CRGBA::CRGBA(80, 30, 30, 40));
		//color_health = CRGBA::CRGBA(90, 0, 0, 255);
	}

	//Implement Blinking
	//if (LastHealth > player->m_fHealth)
	//{
	//	m_EnergyLostTimer = 0;
	//	m_EnergyLostState = BLINK_OFF;
	//}

	//if (m_EnergyLostTimer > 500.0)
	//{
	//	m_EnergyLostState = NO_BLINK;
	//	m_EnergyLostTimer = 0;
	//}
	//else if (m_EnergyLostState != NO_BLINK)
	//{
	//	m_EnergyLostTimer += CTimer::ms_fTimeStep*10 ;

	//	float test_BLINK = m_EnergyLostTimer / 500.0f;
	//	if (test_BLINK > 0.10 && test_BLINK < 0.45 ||  test_BLINK > 0.65 && test_BLINK < 0.80)
	//		m_EnergyLostState = BLINK_ON;
	//	else
	//		m_EnergyLostState = BLINK_OFF;
	//}
	LastHealth = player->m_fHealth;
	m_EnergyLostState = NO_BLINK;

	//CSprite2d::DrawRect(CRect::CRect(x_fac(10.0f), y_fac(448.0f-21.0f), x_fac(110.0f), y_fac(448.0f - 4.0f)), CRGBA::CRGBA(50, 50, 50, 190));
	//CSprite2d::DrawBarChart(x_fac(11.0f), y_fac(448.0f - 20.0f), x_fac(98.0f), y_fac(7.0f), percentage_health, 0, 0, 0, color_health, color_health);
	//CSprite2d::DrawRect(CRect::CRect(CHud::x_fac(20.0), CHud::y_fac(464.0f), CHud::x_fac(98.0f), CHud::y_fac(465.0f + 8.0f)), CRGBA::CRGBA(30, 30, 30, 180));
	//CSprite2d::DrawBarChart(x_fac(11.0f), y_fac(448.0f - 12.0f), x_fac(98.0f), y_fac(7.0f), percentage_armor, 0, 0, 0, color_armor, color_armor);
	float x[100];
	float y[100];
	float x2[100];
	float y2[100];
	int Degree = 180;
	int DegreeStep = 5;
	int Polycount = 360 / DegreeStep;

	for (int i = 0; i < Polycount; i++)
	{
		x[i] = sin(Degree*3.141 / 180);
		y[i] = cos(Degree*3.141 / 180);

		x2[i] = x_fac(x[i] * Health_Radius + Health_PosX);
		y2[i] = y_fac(y[i] * Health_Radius + 448 - Health_PosY);
		x[i] = x_fac(x[i] * Health_innerRadius + Health_PosX);
		y[i] = y_fac(y[i] * Health_innerRadius + 448 - Health_PosY);
		Degree += DegreeStep;
	}

	int index_health = min(Polycount / 2, ceil((Polycount - 1) * percentage_health / 200));
	int percent = ceil((Polycount - 1) *(percentage_armor / 200 + percentage_health / 200));

	for (int i = 0; i < percent; i++)
	{
		if (i == Polycount - 2)
			CSprite2d::Draw2DPolygon(x[i], y[i], x2[i], y2[i], x[0], y[0], x2[0], y2[0], color_armor);
		else if (i < index_health && 	m_EnergyLostState != BLINK_OFF)
			CSprite2d::Draw2DPolygon(x[i], y[i], x2[i], y2[i], x[i + 1], y[i + 1], x2[i + 1], y2[i + 1], color_health);
		else if (i >= index_health)
			CSprite2d::Draw2DPolygon(x[i], y[i], x2[i], y2[i], x[i + 1], y[i + 1], x2[i + 1], y2[i + 1], color_armor);
	}
}

void CHud::DrawWeaponInfo(CPed *player, float y_off)
{
	float alpha = 0;
	static int l_lastammo;
	eTaskType activetask = player->m_pIntelligence->m_TaskMgr.GetActiveTask()->GetId();
	int cammode = TheCamera.m_aCams[TheCamera.m_nActiveCam].m_eMode;

	if (m_LastWeapon != player->m_aWeapons[player->m_nActiveWeaponSlot].m_nType || activetask == TASK_SIMPLE_USE_GUN
		|| player->m_aWeapons[player->m_nActiveWeaponSlot].m_nState == 1 || cammode == MODE_AIMWEAPON || KeyPressed(VK_TAB)
		|| player->m_aWeapons[player->m_nActiveWeaponSlot].m_nTotalAmmo != l_lastammo)
	{
		l_lastammo = player->m_aWeapons[player->m_nActiveWeaponSlot].m_nTotalAmmo;
		m_LastWeapon = player->m_aWeapons[player->m_nActiveWeaponSlot].m_nType;
		m_WeaponTimer = 0;
		if (m_WeaponState == STATE_ON)
			m_WeaponState = STATE_ON;
		else
			m_WeaponState = STATE_FADE_ON;
	}

	switch (m_WeaponState)
	{
	case STATE_OFF:
		alpha = 0;
		break;
	case STATE_FADE_ON:
		m_WeaponFadeTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
		alpha = m_WeaponFadeTimer / 400.0f * 255.0f;
		if (m_WeaponFadeTimer > 400)
		{
			m_WeaponFadeTimer = 0;
			m_WeaponState = STATE_ON;
			alpha = 255;
		}
		break;
	case 5:
	case STATE_ON:
		m_WeaponTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;

		if (m_WeaponTimer > 5000)
		{
			m_WeaponState = STATE_FADE_OFF;
			m_WeaponFadeTimer = 600;
		}

		alpha = 255;
		break;
	case STATE_FADE_OFF:
		//alpha = 255;
		m_WeaponFadeTimer += CTimer::ms_fTimeStep * 0.02 * -1000.0;
		if (m_WeaponFadeTimer < 0.0)
		{
			m_WeaponFadeTimer = 0;
			m_WeaponState = STATE_OFF;
		}
		alpha = m_WeaponFadeTimer / 600.0f * 255.0f;
		break;
	default:
		break;
	}
	DrawWeaponIcon(player, alpha, y_off);
	DrawWeaponAmmo(player, alpha, y_off);
}

void CHud::DrawWeaponIcon(CPed *player, float alpha, float y_off)
{
	CRect Icon;

	RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, reinterpret_cast<void *>(rwFILTERLINEAR));
	int weapModel = CWeaponInfo::GetWeaponInfo(player->m_aWeapons[player->m_nActiveWeaponSlot].m_nType, 1)->m_dwModelId1;
	if (weapModel <= 0)
	{
		CRect Icon = CRect(RsGlobal.maximumWidth - x_fac(120.0f), y_fac(40.0f + y_off), RsGlobal.maximumWidth - x_fac(30.0f), y_fac(40.0f + y_off + 50.0f));
		CHud::Sprites[0].Draw(Icon, CRGBA(255, 255, 255, alpha));
	}
	else {
		CModelInfo::GetModelInfo(weapModel);
		CBaseModelInfo *model = CModelInfo::GetModelInfo(weapModel);
		CTexDictionary *txd = CTxdStore::ms_pTxdPool->GetAt(model->m_wTxdIndex);
		if (txd && txd->m_pRwDictionary)
		{

			RwTexture *iconTex = RwTexDictionaryFindNamedTexture(txd->m_pRwDictionary, "icon");
			if (!iconTex)
				iconTex = RwTexDictionaryFindHashNamedTexture(txd->m_pRwDictionary, CKeyGen::AppendStringToKey(model->m_dwKey, "ICON"));

			if (iconTex) {
				//RwRenderStateSet(rwRENDERSTATEZTESTENABLE, 0);
				//RwRenderStateSet(rwRENDERSTATETEXTURERASTER, iconTex->raster);
				/*CSprite::RenderOneXLUSprite(RsGlobal.maximumWidth - x_fac(30.0f + 100.0f / 2),
					y_fac(40.0f + 50.0f / 2 + y_off), 1.0f, x_fac(100.0f / 2),
					y_fac(50.0f / 2), 255, 255, 255, 255, 1.0f, alpha, 0, 0);*/
				CTxdStore::PushCurrentTxd();
				if (iconTex->raster->height == iconTex->raster->width)
					Icon = CRect(RsGlobal.maximumWidth - x_fac(130.0f - 50), y_fac(40.0f + y_off), RsGlobal.maximumWidth - x_fac(30.0f), y_fac(40.0f + y_off + 50.0f));
				else
					Icon = CRect(RsGlobal.maximumWidth - x_fac(130.0f), y_fac(40.0f + y_off), RsGlobal.maximumWidth - x_fac(30.0f), y_fac(40.0f + y_off + 50.0f));
				CSprite2d Test = CSprite2d::CSprite2d();
				CTxdStore::SetCurrentTxd(model->m_wTxdIndex);
				Test.SetTexture(iconTex->name);
				Test.Draw(Icon, CRGBA(255, 255, 255, alpha));
				CTxdStore::PopCurrentTxd();
				//RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
			}
		}
	}
}

void CHud::DrawWeaponAmmo(CPed *player, float alpha, float y_off)
{
	int weap = player->m_aWeapons[player->m_nActiveWeaponSlot].m_nType;
	int weap_AmmoInClip = player->m_aWeapons[player->m_nActiveWeaponSlot].m_nAmmoInClip;
	int weap_totalAmmo = player->m_aWeapons[player->m_nActiveWeaponSlot].m_nTotalAmmo - weap_AmmoInClip;
	int max_weapammo = CWeaponInfo::GetWeaponInfo(player->m_aWeapons[player->m_nActiveWeaponSlot].m_nType, 1)->m_wAmmoClip;
	if (weap < 15 || weap == WEAPON_PARACHUTE || weap == WEAPON_NIGHTVISION
		|| weap == WEAPON_DETONATOR || weap == WEAPON_INFRARED)
		return;

	char string[40];
	CFont::SetProp(true);
	CFont::SetBackground(false, false);
	CFont::SetDropColor(CRGBA::CRGBA(30, 30, 30, alpha));
	CFont::SetFontStyle(FONT_PRICEDOWN);
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetOutlinePosition(1);
	CFont::SetScale(CHud::x_fac(0.3f), CHud::y_fac(0.6f));
	if (max_weapammo > 1 && weap_AmmoInClip < 1000)
	{
		CFont::SetColor(CRGBA::CRGBA(100, 100, 100, alpha));
		sprintf(string, "%d", weap_AmmoInClip);
		CFont::PrintString(RsGlobal.maximumWidth - x_fac(35.0f), y_fac(30.0f + y_off), string);
		CFont::SetColor(CRGBA::CRGBA(200, 200, 200, alpha));
		sprintf(string, "%d", weap_totalAmmo);
		CFont::PrintString(RsGlobal.maximumWidth - x_fac(60.0f), y_fac(30.0f + y_off), string);
	}
	else
	{
		CFont::SetColor(CRGBA::CRGBA(100, 100, 100, alpha));
		sprintf(string, "%d", weap_totalAmmo);
		CFont::PrintString(RsGlobal.maximumWidth - x_fac(35.0f), y_fac(30.0f + y_off), string);
	}

}

void CHud::DrawWantedLevel(CPed *player)
{
	static int m_Blinkstate = 0;
	static int m_WantedChange = 0;
	static int m_WantedDelta = 0;
	bool show = 0;
	static int counter = 0;
	int WantedLevel = FindPlayerWanted(-1)->m_dwWantedLevel;
	CWanted *pWanted = FindPlayerWanted(-1);
	float alphavalue = 255.0;
	int  WantedLevelBeforeParole = pWanted->m_dwWantedLevelBeforeParole;
	char WantedText[5];
	char Stringshow[5];
	WantedText[0] = 93;
	WantedText[1] = 0;
	enum eBlinkstate
	{
		NO_BLINK,
		BLINK
	};

	if (m_LastWanted != WantedLevel)
	{
		if (m_Blinkstate == NO_BLINK)
			m_WantedFadeTimer = 0;

		if (m_LastWanted > WantedLevel)
			counter = WantedLevel;
		else if (WantedLevel > m_LastWanted)
			counter = m_LastWanted;
		m_WantedDelta = abs(m_LastWanted - WantedLevel);
		m_Blinkstate = BLINK;
	}

	if (m_Blinkstate == BLINK)
	{
		m_WantedFadeTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
		if (m_WantedFadeTimer > 2000)
		{
			m_LastWanted = WantedLevel;
			m_Blinkstate = NO_BLINK;
			counter = WantedLevel;
		}
	}
	if (WantedLevel > 0 || m_Blinkstate == BLINK)
	{
		CFont::SetProp(true);
		CFont::SetBackground(false, false);
		CFont::SetFontStyle(FONT_GOTHIC);
		CFont::SetAlignment(ALIGN_CENTER);
		CFont::SetOutlinePosition(0);

		//DRAW WANTEDSTARS BACKGROUND
		CFont::SetScale(CHud::x_fac(0.4f), CHud::y_fac(0.8f));
		CFont::SetColor(CRGBA::CRGBA(0, 0, 0, 140));
		CFont::SetDropColor(CRGBA::CRGBA(10, 10, 10, 160));
		float posx = 38.0f;
		for (int i = 0; i < 5; i++)
		{
			AsciiToGxtChar(WantedText, Stringshow);
			CFont::PrintString(RsGlobal.maximumWidth - x_fac(posx), y_fac(13.3f), Stringshow);
			posx += 12.0f;
		}

		//DRAW WANTEDSTARS
		CFont::SetScale(CHud::x_fac(0.3f), CHud::y_fac(0.6f));
		CFont::SetColor(CRGBA::CRGBA(255, 255, 255, alphavalue));
		CFont::SetDropColor(CRGBA::CRGBA(30, 30, 30, alphavalue));
		posx = 38.0f;
		for (int i = 0; i < counter; i++)
		{
			AsciiToGxtChar(WantedText, Stringshow);
			CFont::PrintString(RsGlobal.maximumWidth - x_fac(posx), y_fac(15.0f), Stringshow);
			posx += 12.0f;
		}

		if (m_Blinkstate == BLINK)
		{
			float test = m_WantedFadeTimer / 2000.0f;
			if (test > 0.15 && test < 0.3 || test > 0.45 && test < 0.60 || test > 0.75 && test < 0.90)
			{
				for (int i = 0; i < m_WantedDelta; i++)
				{
					AsciiToGxtChar(WantedText, Stringshow);
					CFont::PrintString(RsGlobal.maximumWidth - x_fac(posx), y_fac(15.0f), Stringshow);
					posx += 12.0f;
				}
			}
		}
	}
}

float CHud::DrawMoneyInfo(CPed *player)
{
	enum Showstate
	{
		OFF,
		Move_posy,
		Fade_in,
		ON,
		Fade_Out
	};

	static Showstate m_Moneystate = OFF;
	static int m_Lastmoney = 0;
	static int m_MoneyTimer = 0;
	static int m_MoneyFadeTimer = 0;
	static int m_MoneyMoveTimer = 0;
	static int m_MoneyDelta = 0;
	float alpha = 255.0f;
	char string[40];
	int m_Money = CWorld::Players[CWorld::PlayerInFocus].m_dwMoney;
	float posy = 15.0f;
	float posy_money_change = 15.0f;

	if (m_Money != m_Lastmoney || KeyPressed(VK_TAB))
	{

		if (m_Money != m_Lastmoney)
			m_MoneyDelta = m_Money - m_Lastmoney;

		if (m_Moneystate == ON)
			m_MoneyTimer = 0;
		else
		{
			m_Moneystate = Move_posy;
			m_MoneyTimer = 0;
			m_MoneyMoveTimer = 0;
		}
	}

	switch (m_Moneystate)
	{
	case OFF:
		alpha = 0;
		posy = 0.0f;
		break;
	case Move_posy:
		m_MoneyMoveTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
		if (m_MoneyMoveTimer > 200)
			m_Moneystate = Fade_in;
		posy = m_MoneyMoveTimer / 200.0f * posy_money_change;
		alpha = 0;
		break;
	case Fade_in:
		alpha = 255;
		m_Moneystate = ON;
		posy = posy_money_change;
		break;
	case ON:
		m_MoneyTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
		if (m_MoneyTimer > 7000)
		{
			m_Moneystate = Fade_Out;
			m_MoneyFadeTimer = 600;
			m_MoneyMoveTimer = 200;
		}
		if (m_MoneyTimer > 4000)
			m_MoneyDelta = 0;
		posy = posy_money_change;
		alpha = 255;
		break;
	case Fade_Out:
		m_MoneyFadeTimer += CTimer::ms_fTimeStep * 0.02 * -1000.0;
		if (m_MoneyFadeTimer < 0.0)
			m_MoneyFadeTimer = 0;

		alpha = m_MoneyFadeTimer / 600.0f * 255.0f;
		if (alpha == 0.0f)
		{
			m_MoneyMoveTimer += CTimer::ms_fTimeStep * 0.02 * -1000.0;
			if (m_MoneyMoveTimer < 0.0)
				m_Moneystate = OFF;
			posy = m_MoneyMoveTimer / 200.0f * posy_money_change;
		}
		break;
	default:
		break;
	}
	m_Lastmoney = m_Money;

	CFont::SetProp(true);
	CFont::SetBackground(false, false);
	CFont::SetFontStyle(FONT_PRICEDOWN);
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetOutlinePosition(1);
	CFont::SetScale(CHud::x_fac(0.3f), CHud::y_fac(0.6f));
	CFont::SetDropColor(CRGBA::CRGBA(30, 30, 30, alpha));
	CFont::SetColor(CRGBA::CRGBA(200, 200, 200, alpha));
	sprintf(string, "$%d", m_Money);
	CFont::PrintString(RsGlobal.maximumWidth - x_fac(35.0f), y_fac(30.0f), string);

	if (m_MoneyDelta != 0)
	{
		posy += 15.0f;
		if (m_MoneyDelta > 0)
			sprintf(string, " + $%d", m_MoneyDelta);
		else
			sprintf(string, " - $%d", abs(m_MoneyDelta));

		CFont::PrintString(RsGlobal.maximumWidth - x_fac(35.0f), y_fac(42.0f), string);
	}
	return posy;
}

void CHud::DrawZoneText()
{
	float Fontalpha = 255.0;
	if (m_ZoneName && m_ZoneName != m_LastZoneName)
	{
		switch (m_ZoneState)
		{
		case 0:
			if (!CTheScripts::PlayerisOffMap && CTheScripts::DisplayHud)
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


		if (m_Message || unknownA != 0.0f || unknownB != 0.0)
		{
			m_ZoneState = 3;
		}
		else
		{
			CHud::m_ZoneNameTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
			CFont::SetAlignment(ALIGN_RIGHT);
			CFont::SetProp(true);
			CFont::SetBackground(false, false);
			CFont::SetScale(x_fac(0.5f), y_fac(0.7f));
			CFont::SetOutlinePosition(1);
			CFont::SetDropColor(CRGBA::CRGBA(30, 30, 30, Fontalpha));
			CFont::SetFontStyle(2);
			CFont::SetColor(CRGBA::CRGBA(180, 180, 180, Fontalpha));
			CFont::PrintStringFromBottom(RsGlobal.maximumWidth - x_fac(30.0), RsGlobal.maximumHeight - y_fac(20.0), m_ZonetoPrint);

		}
	}


}

void CHud::DrawCarName()
{
	float Fontalpha = 255.0;
	if (!m_VehicleName)
	{
		m_VehicleState = 0;
		m_VehicleNameTimer = 0;
		m_VehicleFadeTimer = 0;
		m_LastVehicleName = 0;
		return;
	}

	if (m_VehicleName != m_LastVehicleName)
	{
		if (m_VehicleState == STATE_ON)
			m_VehicleNameTimer = 0;
		else
		{
			m_VehicleState = STATE_FADE_ON;
			m_VehicleNameTimer = 0;
			m_VehicleFadeTimer = 0;
		}
		m_LastVehicleName = m_VehicleName;
	}

	switch (m_VehicleState)
	{
	case STATE_OFF:
		Fontalpha = 0;
		break;
	case STATE_FADE_ON:
		m_VehicleFadeTimer += CTimer::ms_fTimeStep * 0.02 * 1000.0;
		if (m_VehicleFadeTimer > 1000.0)
		{
			m_VehicleFadeTimer = 1000;
			m_VehicleState = STATE_ON;
		}
		Fontalpha = m_VehicleFadeTimer * 0.001 * 255.0;
		break;

	case STATE_ON:
		if (m_VehicleNameTimer > 3000.0)
		{
			m_VehicleState = STATE_FADE_OFF;
			m_VehicleFadeTimer = 1000;
		}
		Fontalpha = 255.0;
		break;
	case STATE_FADE_OFF:
		m_VehicleFadeTimer += CTimer::ms_fTimeStep * 0.02 * -1000.0;
		if (m_VehicleFadeTimer < 0)
		{
			m_VehicleNameTimer = 0;
			m_VehicleState = STATE_OFF;
			m_VehicleFadeTimer = 0;
		}
		Fontalpha = m_VehicleFadeTimer * 0.001 * 255.0;
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
		CFont::SetScale(x_fac(0.5f), y_fac(0.7f));
		CFont::SetOutlinePosition(1);
		CFont::SetDropColor(CRGBA::CRGBA(30, 30, 30, max(Fontalpha, 0.0f)));
		CFont::SetFontStyle(2);
		CFont::SetColor(CRGBA::CRGBA(100, 100, 100, Fontalpha));
		CFont::PrintString(RsGlobal.maximumWidth - x_fac(30.0), RsGlobal.maximumHeight - y_fac(45.0), m_VehicleName);
	}
}

void CHud::DrawWastedArrested()
{

}

void CHud::Initialise() {
	//plugin::Call<0x5BA850>();


	int	txd = CTxdStore::AddTxdSlot("hud");
	CTxdStore::LoadTxd(txd, "MODELS\\HUD.TXD");
	CTxdStore::AddRef(txd);
	CTxdStore::PushCurrentTxd();
	CTxdStore::SetCurrentTxd(txd);

	for (int i = 0; i < 6; i++)
		Sprites[i].SetTexture(Spritenames[i]);

	for (int i = 0; i < 2; i++)
		NewRadarSprites[i].SetTexture(NewSpritesNames[i]);

	CTxdStore::PopCurrentTxd();
	ReInitialise();
}

void CHud::Shutdown() {
	//plugin::Call<0x588850>();
	int HUDTxd = CTxdStore::FindTxdSlot("hud");
	CTxdStore::RemoveTxdSlot(HUDTxd);

	for (int i = 0; i < 6; ++i)
		Sprites[i].Delete();

	for (int i = 0; i < 2; i++)
		NewRadarSprites[i].Delete();
}

void CHud::ReInitialise() {
	plugin::Call<0x588880>();
}

void CHud::DrawRadar() {
	//	plugin::Call<0x58A330>();
	if (FrontEndMenuManager.m_dwRadarMode != 2 && (m_ItemToFlash != 8 || CTimer::m_FrameCounter & 8))
	{
		RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)2);
		RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATESHADEMODE, (void*)1);
		CRadar::DrawMap();
		if (FindPlayerVehicle(-1, 0) && FindPlayerVehicle(-1, 0)->m_dwVehicleSubClass == VEHICLE_PLANE && FindPlayerVehicle(-1, 0)->m_wModelIndex != 539)
		{
			// Draw inside Radar here (for planes)
		}

		//Draw Radaring around radar only if Hud is on
		if (FrontEndMenuManager.m_bHudOn)
		{		
			float scaleRadius = Health_Radius + 1.5;
			CRect Icon = CRect(x_fac(Health_PosX - scaleRadius), y_fac(448 - Health_PosY + scaleRadius), x_fac(Health_PosX + scaleRadius), y_fac(448 - Health_PosY - scaleRadius));
			CHud::NewRadarSprites[0].Draw(Icon, CRGBA(255, 255, 255, 180));
		}

	}
	if (FrontEndMenuManager.m_dwRadarMode < 2)
	CRadar::DrawBlips();

}

void CHud::DrawCrosshairs()
{
	CPlayerPed *playerPed; // edi
	WORD mode1; // ax
	BOOL bSimpleAim; // bl
	WORD mode2; // ax
	ePedState unused; // eax
	eWeaponType v6; // eax
	double v8; // st7
	CRGBA color; // eax
	//double v10; // st7
	//double v11; // st6
	//double v12; // st5
	//float v13; // ST58_4
	//double v14; // st5
	//float v15; // ST4C_4
	//float v16; // ST54_4
	//double v17; // st7
	//float v18; // ST50_4
	//double v19; // st7
	//float v20; // ST4C_4
	//CRGBA *v21; // eax
	//double v22; // st7
	//CRGBA *v23; // eax
	//double v24; // st7
	//CRGBA *v25; // eax
	//CRGBA *v26; // eax
	//WORD mode5; // ax
	//double v28; // st7
	//double v29; // st6
	//float v30; // ST58_4
	//float v31; // ST54_4
	//double v32; // st7
	//float v33; // ST50_4
	//double v34; // st7
	//float v35; // ST4C_4
	//CRGBA *v36; // eax
	//double v37; // st7
	//CRGBA *v38; // eax
	//double v39; // st7
	//CRGBA *v40; // eax
	//CRGBA *v41; // eax
	//CPed *v42; // eax
	//CPed *v43; // eax
	//WORD mode6; // ax
	//RwTexture *texCrosshair; // esi
	//double v46; // st7
	//double v47; // st6
	//CPed *v48; // eax
	//double v49; // st7
	//int modelId; // eax
	//CPedModelInfo *model; // eax
	//int txdIndex; // ecx
	//RwTexDictionary **pTxd; // ecx
	//RwTexDictionary *txd; // esi
	//int key; // eax
	//float v56; // ST54_4
	//float v57; // ST58_4
	//float v58; // ST0C_4
	//float v59; // ST08_4
	//float v60; // ST0C_4
	//float v61; // ST08_4
	//float v62; // ST0C_4
	//float v63; // ST08_4
	//float v64; // ST0C_4
	//float v65; // ST08_4
	char bDrawCrosshair; // [esp+43h] [ebp-2Dh]
	//float v67; // [esp+44h] [ebp-2Ch]
	//float v68; // [esp+48h] [ebp-28h]
	//float v69; // [esp+48h] [ebp-28h]
	//float v70; // [esp+4Ch] [ebp-24h]
	float _crosshairSizeMP; // [esp+50h] [ebp-20h]
	//float _crosshairSizeMPa; // [esp+50h] [ebp-20h]
	//int v73; // [esp+54h] [ebp-1Ch]
	//float v74; // [esp+58h] [ebp-18h]
	//float v75; // [esp+5Ch] [ebp-14h]
	//CRect coords; // [esp+60h] [ebp-10h]

	playerPed = FindPlayerPed();
	mode1 = TheCamera.m_aCams[TheCamera.m_nActiveCam].m_eMode;
	bSimpleAim = 0;
	bDrawCrosshair = 0;
	if (mode1 == MODE_SNIPER)
		return;
	if (mode1 == MODE_1STPERSON)
	{
		if (FindPlayerVehicle(-1, 0) && (FindPlayerVehicle(-1, 0)->m_wModelIndex == 520 || FindPlayerVehicle(-1, 0)->m_wModelIndex == 425))
			bDrawCrosshair = 1;
	}

	if (TheCamera.m_aCams[TheCamera.m_nActiveCam].m_eMode != MODE_1STPERSON
		&& !playerPed->m_aWeapons[playerPed->m_nActiveWeaponSlot].IsTypeMelee())
		bDrawCrosshair = 1;

	if (mode1 == MODE_M16_1STPERSON_RUNABOUT || 
		mode1 == MODE_ROCKETLAUNCHER_RUNABOUT || 
		mode1 == MODE_ROCKETLAUNCHER_RUNABOUT_HS || 
		mode1 == MODE_SNIPER_RUNABOUT)
		bSimpleAim = 1;


	if (!playerPed->m_pTargetedObject && playerPed->m_pPlayerData->m_bFreeAiming
		&& (!playerPed->m_pIntelligence->GetUseGunTask() || playerPed->m_pIntelligence->GetUseGunTask()->field_E))
	{
		if (mode1 == MODE_AIMWEAPON || mode1 == MODE_AIMWEAPON_FROMCAR || mode1 == MODE_AIMWEAPON_ATTACHED)
		{
			if (playerPed->m_pedState != 59 && playerPed->m_pedState != 57)
			{
				if ((v6 = playerPed->m_aWeapons[playerPed->m_nActiveWeaponSlot].m_nType, v6 >= WEAPON_PISTOL)
					&& v6 <= WEAPON_M4
					|| v6 == WEAPON_TEC9
					|| v6 == WEAPON_COUNTRYRIFLE
					|| v6 == WEAPON_MINIGUN
					|| v6 == WEAPON_FTHROWER)
				{
					bSimpleAim = mode1 != MODE_AIMWEAPON || !TheCamera.m_bTransitionState;
				}
			}
		}
	}
	if (bDrawCrosshair || bSimpleAim || CTheScripts::bDrawCrossHair)// IF AIM
	{
		RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)2);
		RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)0);

		if (mode1 == MODE_AIMWEAPON || mode1 == MODE_AIMWEAPON_FROMCAR || mode1 == MODE_AIMWEAPON_ATTACHED)
		{

			_crosshairSizeMP = playerPed->GetWeaponRadiusOnScreen();;
			float widthfac = 0.53*RsGlobal.maximumWidth;
			float heightfac = 0.38* RsGlobal.maximumHeight;
			CRect Rect = CRect(widthfac - x_fac(0.5f), heightfac + y_fac(0.5f), widthfac + x_fac(0.5f), heightfac - y_fac(0.5f));
			CSprite2d::DrawRect(Rect, CRGBA::CRGBA(230, 230, 230, 255));


			//left top
			Rect = CRect(widthfac - x_fac(10.0f), heightfac - y_fac(10.0f), widthfac, heightfac);
			Sprites[1].Draw(Rect, CRGBA::CRGBA(255, 255, 255, 255));
			//Right top
			Rect = CRect(widthfac + x_fac(10.0f), heightfac - y_fac(10.0f), widthfac , heightfac);
			Sprites[1].Draw(Rect, CRGBA::CRGBA(255, 255, 255, 255));
			//Left bottom
			Rect = CRect(widthfac - x_fac(10.0f), heightfac + y_fac(10.0f), widthfac, heightfac);
			Sprites[1].Draw(Rect, CRGBA::CRGBA(255, 255, 255, 255));
			//Right bottomm
			Rect = CRect(widthfac + x_fac(10.0f), heightfac + y_fac(10.0f), widthfac, heightfac);
			Sprites[1].Draw(Rect, CRGBA::CRGBA(255, 255, 255, 255));

		}

	}
	//if (CTheScripts::bDrawCrossHair != 2)     // FPS M16
	//{
	//	mode5 = TheCamera.m_aCams[TheCamera.m_nActiveCam].m_wMode;
	//	if (mode5 == MODE_M16_1STPERSON
	//		|| mode5 == MODE_M16_1STPERSON_RUNABOUT
	//		|| mode5 == MODE_1STPERSON_RUNABOUT
	//		|| mode5 == MODE_HELICANNON_1STPERSON)
	//	{
	//		v28 = (double)RsGlobal.MaximumWidth * 0.0015625 * 64.0;
	//		v75 = v28;
	//		v29 = (double)RsGlobal.MaximumHeight * 0.002232143 * 64.0;
	//		v74 = v29;
	//		v73 = RsGlobal.MaximumHeight / 2;
	//		v30 = (double)(RsGlobal.MaximumWidth / 2) - v28 * 0.5;
	//		coords.x1 = v30;
	//		v31 = (double)(RsGlobal.MaximumHeight / 2) - v29 * 0.5;
	//		coords.y2 = v31;
	//		v32 = v75 * 0.5 + v30;
	//		v33 = v32;
	//		coords.x2 = v32;
	//		v34 = v74 * 0.5 + v31;
	//		v35 = v34;
	//		coords.y1 = v34;
	//		v36 = CRGBA::CRGBA((CRGBA *)&v73, 255u, 255u, 255u, 255u);
	//		CSprite2d::Draw((CSprite2d *)&CHud::Sprites.siteM16, (CRect *)&coords, v36);
	//		v37 = v30 + v75;
	//		v75 = v37;
	//		coords.x1 = v37;
	//		coords.x2 = v33;
	//		coords.y2 = v31;
	//		coords.y1 = v35;
	//		v38 = CRGBA::CRGBA((CRGBA *)&v73, 255u, 255u, 255u, 255u);
	//		CSprite2d::Draw((CSprite2d *)&CHud::Sprites.siteM16, (CRect *)&coords, v38);
	//		v39 = v31 + v74;
	//		v74 = v39;
	//		coords.y2 = v39;
	//		coords.x1 = v30;
	//		coords.x2 = v33;
	//		coords.y1 = v35;
	//		v40 = CRGBA::CRGBA((CRGBA *)&v73, 255u, 255u, 255u, 255u);
	//		CSprite2d::Draw((CSprite2d *)&CHud::Sprites.siteM16, (CRect *)&coords, v40);
	//		coords.x1 = v75;
	//		coords.x2 = v33;
	//		coords.y2 = v74;
	//		coords.y1 = v35;
	//		v41 = CRGBA::CRGBA((CRGBA *)&v75, 255u, 255u, 255u, 255u);
	//		CSprite2d::Draw((CSprite2d *)&CHud::Sprites.siteM16, (CRect *)&coords, v41);
	//		@@return:
	//			RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATESRCBLEND, 5u);
	//		RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEDESTBLEND, 6u);
	//		RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, 1u);
	//		return;
	//	}
	//}
	//RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTUREFILTER, 2u);
	//v42 = FindPlayerPed(-1);
	//if (v42->m_aWeapons[v42->m_nActiveWeaponSlot].m_nType == WEAPON_CAMERA
	//	|| (v43 = FindPlayerPed(-1), v43->m_aWeapons[v43->m_nActiveWeaponSlot].m_nType == WEAPON_SNIPERRIFLE)
	//	|| CTheScripts::bDrawCrossHair == 2)
	//{
	//	v48 = FindPlayerPed(-1);
	//	if (v48->m_aWeapons[v48->m_nActiveWeaponSlot].m_nType == WEAPON_CAMERA || CTheScripts::bDrawCrossHair == 2)
	//	{
	//		*(float *)&v73 = (double)RsGlobal.MaximumWidth * 0.0015625 * 256.0;
	//		v49 = (double)RsGlobal.MaximumHeight * 0.002232143 * 192.0;
	//	}
	//	else
	//	{
	//		*(float *)&v73 = (double)RsGlobal.MaximumWidth * 0.0015625 * 210.0;
	//		v49 = (double)RsGlobal.MaximumHeight * 0.002232143 * 210.0;
	//	}
	//	_crosshairSizeMPa = v49;
	//	v67 = 0.0;
	//	v69 = 0.0;
	//	modelId = CWeaponInfo::GetWeaponInfo(playerPed->m_aWeapons[playerPed->m_nActiveWeaponSlot].m_nType, 1)->dwModelId1;
	//	if (modelId <= 0)
	//		goto @@return;
	//		model = CModelInfo::ms_modelInfoPtrs[modelId];
	//	txdIndex = model->clump.base.m_wTxdIndex;
	//	pTxd = (RwTexDictionary **)(CTxdStore::ms_pTxdPool->m_byteMap[txdIndex] >= 0 ? (char *)CTxdStore::ms_pTxdPool->m_pObjects
	//		+ 12 * txdIndex : 0);
	//	txd = *pTxd;
	//	if (!*pTxd)
	//		goto @@return;
	//		key = CKeyGen::AppendStringToKey(model->clump.base.m_dwKey, (int)"CROSSHAIR");
	//	texCrosshair = RwTexDictionaryFindHashNamedTexture(txd, key);
	//}
	//else
	//{
	//	mode6 = TheCamera.m_aCams[TheCamera.m_nActiveCam].m_eMode;
	//	if (mode6 != MODE_ROCKETLAUNCHER
	//		&& mode6 != MODE_1STPERSON
	//		&& mode6 != MODE_ROCKETLAUNCHER_RUNABOUT
	//		&& mode6 != MODE_ROCKETLAUNCHER_HS
	//		&& mode6 != MODE_ROCKETLAUNCHER_RUNABOUT_HS)
	//	{
	//		goto @@return;
	//	}
	//	texCrosshair = (RwTexture *)CHud::Sprites.siterocket;
	//	v46 = (double)RsGlobal.MaximumWidth * 0.0015625;
	//	*(float *)&v73 = 24.0 * v46;
	//	v47 = (double)RsGlobal.MaximumHeight * 0.002232143;
	//	_crosshairSizeMPa = 24.0 * v47;
	//	v69 = v46 * 20.0;
	//	v67 = v47 * 20.0;
	//}
	//if (texCrosshair)
	//{
	//	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE, 0);
	//	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void*)3u);
	//	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTURERASTER, (unsigned int)texCrosshair->raster);
	//	v56 = _crosshairSizeMPa * 0.5;
	//	v57 = *(float *)&v73 * 0.5;
	//	v58 = (double)(RsGlobal.MaximumHeight / 2) - v56 - v67;
	//	v59 = (double)(RsGlobal.MaximumWidth / 2) - v57 - v69;
	//	CSprite::RenderOneXLUSprite(v59, v58, 1.0, v57, v56, 255u, 255u, 255u, 255, 0.0099999998, 255, 0, 0);
	//	v60 = (double)(RsGlobal.MaximumHeight / 2) - v56 - v67;
	//	v61 = (double)(RsGlobal.MaximumWidth / 2) + v57 + v69;
	//	CSprite::RenderOneXLUSprite(v61, v60, 1.0, v57, v56, 255u, 255u, 255u, 255, 0.0099999998, 255, 1, 0);
	//	v62 = (double)(RsGlobal.MaximumHeight / 2) + v56 + v67;
	//	v63 = (double)(RsGlobal.MaximumWidth / 2) - v57 - v69;
	//	CSprite::RenderOneXLUSprite(v63, v62, 1.0, v57, v56, 255u, 255u, 255u, 255, 0.0099999998, 255, 0, 1);
	//	LODWORD(v75) = RsGlobal.MaximumWidth / 2;
	//	v64 = (double)(RsGlobal.MaximumHeight / 2) + v56 + v67;
	//	v65 = (double)(RsGlobal.MaximumWidth / 2) + v57 + v69;
	//	CSprite::RenderOneXLUSprite(v65, v64, 1.0, v57, v56, 255u, 255u, 255u, 255, 0.0099999998, 255, 1, 1);
	//	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
	//}
	//goto @@return;

}