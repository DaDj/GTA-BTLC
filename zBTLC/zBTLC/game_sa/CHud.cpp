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

char (*CHud::m_BigMessage)[128] = (char (*)[128])0xBAACC0;
Bool &CHud::bScriptForceDisplayWithCounters = *(Bool *)0xBAA3FA;

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
	float height_fac = RsGlobal.maximumHeight / 480.0f;
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
	CFont::SetScale(CHud::x_fac(0.4f), CHud::y_fac(0.4f));
	CFont::PrintString(CHud::x_fac(540.0f),CHud::y_fac(10.0f), string);

	CHud::DrawPlayerhealthandarmor(player);
}


void CHud::DrawPlayerhealthandarmor(CPed *player)
{
	static unsigned int lastdamagetaken;


	

	float percentage_health = (player->m_fHealth / player->m_fMaxHealth) * 100;
	CRGBA color_health = CRGBA::CRGBA(0, 90, 0, 240);
	float percentage_armor = player->m_fArmour ;
	CRGBA color_armor = CRGBA::CRGBA(200, 200, 210, 240);


	if (percentage_health < 30) 
		color_health = CRGBA::CRGBA(90, 0, 0, 255);
	

	lastdamagetaken = CWorld::Players[CWorld::PlayerInFocus].m_dwLastTimeEnergyLost;
	//CSprite2d::DrawRect(CRect::CRect(CHud::x_fac(29.0f), CHud::y_fac(400.0f), CHud::x_fac(99.0f), CHud::y_fac(455.0f + 8.0)), CRGBA::CRGBA(30, 30, 30, 180));
	

	if (CTimer::m_snTimeInMilliseconds < (lastdamagetaken + 100))
	{
		CSprite2d::DrawRect(CRect::CRect(CHud::x_fac(0.0f), CHud::y_fac(0.0f), CHud::x_fac(640.0f), CHud::y_fac(480.0f)), CRGBA::CRGBA(30, 30, 30, 40));
	}

	if (!CTimer::m_snTimeInMilliseconds < (lastdamagetaken + 4000) || KeyPressed(VK_TAB))
	{

		CSprite2d::DrawRect(CRect::CRect(CHud::x_fac(10.0f), CHud::y_fac(459.0f), CHud::x_fac(100.0f), CHud::y_fac(477.0f)), CRGBA::CRGBA(30, 30, 30, 180));
		CSprite2d::DrawBarChart(CHud::x_fac(11.0f), CHud::y_fac(461.0f), CHud::x_fac(88.0f), CHud::y_fac(6.0f), percentage_health, 0, 0, 0, color_health, CRGBA::CRGBA(0, 100, 0, 255));

		//CSprite2d::DrawRect(CRect::CRect(CHud::x_fac(20.0), CHud::y_fac(464.0f), CHud::x_fac(98.0f), CHud::y_fac(465.0f + 8.0f)), CRGBA::CRGBA(30, 30, 30, 180));
		CSprite2d::DrawBarChart(CHud::x_fac(11.0f), CHud::y_fac(469.0f), CHud::x_fac(88.0f), CHud::y_fac(6.0f), percentage_armor, 0, 0, 0, color_armor, CRGBA::CRGBA(10, 100, 10, 255));
	}
}