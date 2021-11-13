#include "CRadar.h"
#include "CMenuManager.h"
#include "RenderWare.h"
#include "CHud.h"
#include "CPad.h"
#include "CHudColours.h"
#include "CText.h"
#include "CFont.h"

float CRadar::Radar_Height = 70.0f;
float CRadar::Radar_Width = 100.0f;
float CRadar::Radar_Posx = 10.0f;
float CRadar::Radar_Posy = 23.0f;

unsigned int MAX_RADAR_SPRITES = 64;
unsigned int MAX_RADAR_TRACES = 175;
unsigned int MAX_AIRSTRIP_INFOS = 4;
unsigned int MAX_RADAR_WIDTH_TILES = 12;
unsigned int MAX_RADAR_HEIHGT_TILES = 12;

float &CRadar::m_radarRange = *(float *)0xBA8314;
unsigned short *CRadar::MapLegendList = (unsigned short *)0xBA8318;
unsigned short &CRadar::MapLegendCounter = *(unsigned short *)0xBA86B8;
CRGBA *CRadar::ArrowBlipColour = (CRGBA *)0xBA86D4;
tRadarTrace *CRadar::ms_RadarTrace = (tRadarTrace *)0xBA86F0;
CVector2D &CRadar::vec2DRadarOrigin = *(CVector2D *)0xBAA248;
CSprite2d *CRadar::RadarBlipSprites = (CSprite2d *)0xBAA250;
CRect &CRadar::m_radarRect = *(CRect *)0x8D0920;
unsigned char &CRadar::airstrip_location = *(unsigned char *)0xBA8300;
int &CRadar::airstrip_blip = *(int *)0xBA8304;
airstrip_info *airstrip_table = (airstrip_info *)0x8D06E0;
int *gRadarTextures = (int *)0xBA8478;


void CRadar::My_Init()
{
//#define RECTRADAR

	CRadar::Radar_Height = CHud::Health_innerRadius * 2 ;
	CRadar::Radar_Width = CHud::Health_innerRadius * 2 ;
	CRadar::Radar_Posx = CHud::Health_PosX  - Radar_Height / 2;
	CRadar::Radar_Posy = CHud::Health_PosY - Radar_Height / 2;
#ifdef  RECTRADAR

	CRadar::Radar_Height = 70.0f;
	CRadar::Radar_Width = 100.0f;
	CRadar::Radar_Posx = 10.0f;
	CRadar::Radar_Posy = 23.0f;

	//Draw radar mask
	MemoryVP::InjectHook(0x585700, &CRadar::DrawRadarMask, PATCH_JUMP);
	//replace original 
	MemoryVP::InjectHook(0x5832F0, &CRadar::LimitRadarPoint, PATCH_JUMP);
#endif 


	//newradartoscreenspace
	MemoryVP::InjectHook(0x583480, &CRadar::TransformRadarPointToScreenSpace, PATCH_JUMP);

	int alpha = 200;
	MemoryVP::Patch<int>(0x586432 + 1, alpha);
	MemoryVP::Patch<int>(0x58647B + 1, alpha);
	MemoryVP::Patch<int>(0x5864BC + 1, alpha);

	injector::MakeJMP(0x58A782, 0x58AA2A); //don't draw the borderthingy
	MemoryVP::Patch<BYTE>(0x58694E + 1, 1); //renderstatetexturalpha
	//MemoryVP::Patch<void*>(0x5834C0 + 2, &radar_width);
}

// Converted from cdecl void CRadar::LoadTextures(void) 0x5827D0
void CRadar::LoadTextures()
{
	((void(__cdecl *)())0x5827D0)();
}

// Converted from cdecl int CRadar::GetNewUniqueBlipIndex(int blipArrId) 0x582820
int CRadar::GetNewUniqueBlipIndex(int blipArrId)
{
	return ((int(__cdecl *)(int))0x582820)(blipArrId);
}

// Converted from cdecl int CRadar::GetActualBlipArrayIndex(int blipIndex) 0x582870
int CRadar::GetActualBlipArrayIndex(int blipIndex)
{
	return ((int(__cdecl *)(int))0x582870)(blipIndex);
}

// Converted from cdecl void CRadar::DrawLegend(int x,int y,int blipType) 0x5828A0
void CRadar::DrawLegend(int x, int y, int blipType)
{
	//((void(__cdecl *)(int, int, int))0x5828A0)(x, y, blipType);

	char *str;
	switch (blipType)
	{
	case 3:
		str = TheText.Get("LG_01");
		break;
	case 5:
		str = TheText.Get("LG_02");
		break;
	case 6:
		str = TheText.Get("LG_03");
		break;
	case 7:
		str = TheText.Get("LG_04");
		break;
	case 8:
		str = TheText.Get("LG_05");
		break;
	case 9:
		str = TheText.Get("LG_06");
		break;
	case 10:
		str = TheText.Get("LG_07");
		break;
	case 12:
		str = TheText.Get("LG_09");
		break;
	case 13:
		str = TheText.Get("LG_10");
		break;
	case 14:
		str = TheText.Get("LG_11");
		break;
	case 15:
		str = TheText.Get("LG_12");
		break;
	case 16:
		str = TheText.Get("LG_13");
		break;
	case 18:
		str = TheText.Get("LG_15");
		break;
	case 19:
		str = TheText.Get("LG_16");
		break;
	case 20:
		str = TheText.Get("LG_17");
		break;
	case 21:
		str = TheText.Get("LG_18");
		break;
	case 22:
		str = TheText.Get("LG_19");
		break;
	case 23:
		str = TheText.Get("LG_20");
		break;
	case 24:
		str = TheText.Get("LG_21");
		break;
	case 25:
		str = TheText.Get("LG_22");
		break;
	case 26:
		str = TheText.Get("LG_23");
		break;
	case 27:
		str = TheText.Get("LG_24");
		break;
	case 28:
		str = TheText.Get("LG_25");
		break;
	case 29:
		str = TheText.Get("LG_26");
		break;
	case 30:
		str = TheText.Get("LG_27");
		break;
	case 31:
		str = TheText.Get("LG_28");
		break;
	case 32:
		str = TheText.Get("LG_29");
		break;
	case 33:
		str = TheText.Get("LG_30");
		break;
	case 34:
		str = TheText.Get("LG_31");
		break;
	case 35:
		str = TheText.Get("LG_32");
		break;
	case 36:
		str = TheText.Get("LG_33");
		break;
	case 63:
		str = TheText.Get("LG_34");
		break;
	case 38:
		str = TheText.Get("LG_35");
		break;
	case 39:
		str = TheText.Get("LG_36");
		break;
	case 40:
		str = TheText.Get("LG_37");
		break;
	case 42:
		str = TheText.Get("LG_39");
		break;
	case 43:
		str = TheText.Get("LG_40");
		break;
	case 44:
		str = TheText.Get("LG_41");
		break;
	case 45:
		str = TheText.Get("LG_42");
		break;
	case 46:
		str = TheText.Get("LG_43");
		break;
	case 47:
		str = TheText.Get("LG_44");
		break;
	case 48:
		str = TheText.Get("LG_45");
		break;
	case 49:
		str = TheText.Get("LG_46");
		break;
	case 50:
		str = TheText.Get("LG_47");
		break;
	case 51:
		str = TheText.Get("LG_48");
		break;
	case 52:
		str = TheText.Get("LG_51");
		break;
	case 53:
		str = TheText.Get("LG_52");
		break;
	case 54:
		str = TheText.Get("LG_53");
		break;
	case 55:
		str = TheText.Get("LG_57");
		break;
	case 58:
		str = TheText.Get("LG_58");
		break;
	case 59:
		str = TheText.Get("LG_59");
		break;
	case 60:
		str = TheText.Get("LG_60");
		break;
	case 61:
		str = TheText.Get("LG_61");
		break;
	case 62:
		str = TheText.Get("LG_62");
		break;
	case 37:
		str = TheText.Get("LG_63");
		break;
	case 41:
		str = TheText.Get("LG_64");
		break;
	case 11:
		str = TheText.Get("LG_66");
		break;
	case 17:
		str = TheText.Get("LG_67");
		break;
	case 57:
		str = TheText.Get("LG_65");
		break;
	case 4294967295:
		str = TheText.Get("LG_49");
		break;
	case 4294967294:
		str = TheText.Get("LG_50");
		break;
	case 4294967293:
		str = TheText.Get("LG_54");
		break;
	case 4294967292:
		str = TheText.Get("LG_55");
		break;
	case 4294967291:
		str = TheText.Get("LG_56");
		break;
	default:
		str = TheText.Get("LG_00");
		break;
	}

	CFont::SetBackground(0, 0);
	CFont::SetProp(1);
	CFont::SetAlignment(ALIGN_LEFT);
	CFont::SetFontStyle(FONT_MENU);
	CFont::SetScale(CHud::x_fac(0.4f), CHud::y_fac(0.35f));
	CFont::SetOutlinePosition(0);
	CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
	CFont::SetDropColor(HudColour.GetRGB(HUD_COLOUR_BLACK, 255));

	CFont::PrintString(x + CHud::x_fac(15.0f), y + CHud::y_fac(5.0f), str);
	

	if (blipType < 0)
	{
		//CSprite2d::Draw2DPolygon()
	}
	else
	{
		CRGBA Color = CRGBA::CRGBA (255, 255, 255, 255);
		CRect BlipRect = CRect::CRect();
		BlipRect.m_fLeft = x ;
		BlipRect.m_fRight = x + CHud::x_fac(15.0f);
		BlipRect.m_fTop = y;
		BlipRect.m_fBottom = y + CHud::y_fac(15.0f);

		CRadar::RadarBlipSprites[blipType].Draw(BlipRect, Color);
		
	}


}

// Converted from cdecl float CRadar::LimitRadarPoint(CVector2D &point) 0x5832F0
float CRadar::LimitRadarPoint(CVector2D& point)
{
	//return ((float(__cdecl *)(CVector2D&))0x5832F0)(point2);
	float Limit_x = 1;
	float Limit_y = 1;
	 
	float result = sqrt( point.x * point.x + point.y * point.y);
	if (result > sqrt(2.f) / 2)
	{
		point.x /= result / sqrt(2.f);
		point.y /= result / sqrt(2.f);
	}
	
	if (!FrontEndMenuManager.drawRadarOrMap)
	{
		point.y = max(-Limit_y, min(Limit_y, point.y));
		point.x = max(-Limit_x, min(Limit_x, point.x));
	}
	else
	{
		point.y = max(-1.0f, min(1.0f, point.y));
		point.x = max(-1.0f, min(1.0f, point.x));
	}
	return result;
}

// Converted from cdecl void CRadar::LimitToMap(float *pX,float *pY) 0x583350
void CRadar::LimitToMap(float* pX, float* pY)
{
	((void(__cdecl *)(float*, float*))0x583350)(pX, pY);
}

// Converted from cdecl uchar CRadar::CalculateBlipAlpha(float distance) 0x583420
unsigned char CRadar::CalculateBlipAlpha(float distance)
{
	return ((unsigned char(__cdecl *)(float))0x583420)(distance);
}

// Converted from cdecl void CRadar::TransformRadarPointToScreenSpace(CVector2D &out,CVector2D const&in) 0x583480
void CRadar::TransformRadarPointToScreenSpace(CVector2D& out, CVector2D& in)
{
	//((void(__cdecl *)(CVector2D&, CVector2D const&))0x583480)(out, in);
	__asm push edx

	if (FrontEndMenuManager.drawRadarOrMap)
	{
		out.x = FrontEndMenuManager.m_fMapZoom * in.x + FrontEndMenuManager.m_fMapBaseX;
		out.y = FrontEndMenuManager.m_fMapBaseY - FrontEndMenuManager.m_fMapZoom * in.y;
	}
	else
	{
		out.x = CHud::x_fac(CRadar::Radar_Posx + CRadar::Radar_Width*0.5) + CHud::x_fac(CRadar::Radar_Width*0.5)* in.x ;
		out.y = RsGlobal.maximumHeight - CHud::y_fac(CRadar::Radar_Posy+ CRadar::Radar_Height*0.5) -  CHud::y_fac(CRadar::Radar_Height*0.5)  *  in.y ;
	}
	__asm pop edx
}



// Converted from cdecl void CRadar::TransformRealWorldPointToRadarSpace(CVector2D &out,CVector2D const&in) 0x583530
void CRadar::TransformRealWorldPointToRadarSpace(CVector2D& out, CVector2D const& in)
{
	((void(__cdecl *)(CVector2D&, CVector2D const&))0x583530)(out, in);
}

// Converted from cdecl void CRadar::TransformRadarPointToRealWorldSpace(CVector2D &out,CVector2D const&in) 0x5835A0
void CRadar::TransformRadarPointToRealWorldSpace(CVector2D& out, CVector2D const& in)
{
	((void(__cdecl *)(CVector2D&, CVector2D const&))0x5835A0)(out, in);
}

// Converted from cdecl void CRadar::TransformRealWorldToTexCoordSpace(CVector2D &out,CVector2D const&in,int,int) 0x583600
void CRadar::TransformRealWorldToTexCoordSpace(CVector2D& out, CVector2D const& in, int arg2, int arg3)
{
	((void(__cdecl *)(CVector2D&, CVector2D const&, int, int))0x583600)(out, in, arg2, arg3);
}

// Converted from cdecl void CRadar::CalculateCachedSinCos(void) 0x583670
void CRadar::CalculateCachedSinCos()
{
	((void(__cdecl *)())0x583670)();
}

// Converted from cdecl int CRadar::SetCoordBlip(eBlipType type,CVector posn,uint,eBlipDisplay blipDisplay, char* scriptName) 0x583820
int CRadar::SetCoordBlip(eBlipType type, CVector posn, unsigned int arg2, eBlipDisplay blipDisplay, char* scriptName)
{
	return ((int(__cdecl *)(eBlipType, CVector, unsigned int, eBlipDisplay, char*))0x583820)(type, posn, arg2, blipDisplay, scriptName);
}

// Converted from cdecl int CRadar::SetShortRangeCoordBlip(eBlipType type,CVector posn,uint,eBlipDisplay blipDisplay, char* scriptName) 0x583920
int CRadar::SetShortRangeCoordBlip(eBlipType type, CVector posn, unsigned int arg2, eBlipDisplay blipDisplay, char* scriptName)
{
	return ((int(__cdecl *)(eBlipType, CVector, unsigned int, eBlipDisplay, char*))0x583920)(type, posn, arg2, blipDisplay, scriptName);
}

// Converted from cdecl int CRadar::SetEntityBlip(eBlipType type,int entityHandle,uint,eBlipDisplay blipDisplay) 0x5839A0
int CRadar::SetEntityBlip(eBlipType type, int entityHandle, unsigned int arg2, eBlipDisplay blipDisplay)
{
	return ((int(__cdecl *)(eBlipType, int, unsigned int, eBlipDisplay))0x5839A0)(type, entityHandle, arg2, blipDisplay);
}

// Converted from cdecl void CRadar::ChangeBlipColour(int blipIndex,uint color) 0x583AB0
void CRadar::ChangeBlipColour(int blipIndex, unsigned int color)
{
	((void(__cdecl *)(int, unsigned int))0x583AB0)(blipIndex, color);
}

// Converted from cdecl bool CRadar::HasThisBlipBeenRevealed(int blipArrId) 0x583AF0
bool CRadar::HasThisBlipBeenRevealed(int blipArrId)
{
	return ((bool(__cdecl *)(int))0x583AF0)(blipArrId);
}

// Converted from cdecl bool CRadar::DisplayThisBlip(int spriteId,signed char priority) 0x583B40
bool CRadar::DisplayThisBlip(int spriteId, char priority)
{
	return ((bool(__cdecl *)(int, signed))0x583B40)(spriteId, priority);
}

// Converted from cdecl void CRadar::ChangeBlipBrightness(int blipIndex,int brightness) 0x583C70
void CRadar::ChangeBlipBrightness(int blipIndex, int brightness)
{
	((void(__cdecl *)(int, int))0x583C70)(blipIndex, brightness);
}

// Converted from cdecl void CRadar::ChangeBlipScale(int blipIndex,int size) 0x583CC0
void CRadar::ChangeBlipScale(int blipIndex, int size)
{
	((void(__cdecl *)(int, int))0x583CC0)(blipIndex, size);
}

// Converted from cdecl void CRadar::ChangeBlipDisplay(int blipIndex,eBlipDisplay blipDisplay) 0x583D20
void CRadar::ChangeBlipDisplay(int blipIndex, eBlipDisplay blipDisplay)
{
	((void(__cdecl *)(int, eBlipDisplay))0x583D20)(blipIndex, blipDisplay);
}

// Converted from cdecl void CRadar::SetBlipSprite(int blipIndex,int spriteId) 0x583D70
void CRadar::SetBlipSprite(int blipIndex, int spriteId)
{
	((void(__cdecl *)(int, int))0x583D70)(blipIndex, spriteId);
}

// Converted from cdecl void CRadar::SetBlipAlwaysDisplayInZoom(int blipIndex,uchar display) 0x583DB0
void CRadar::SetBlipAlwaysDisplayInZoom(int blipIndex, unsigned char display)
{
	((void(__cdecl *)(int, unsigned char))0x583DB0)(blipIndex, display);
}

// Converted from cdecl void CRadar::SetBlipFade(int blipIndex,uchar fade) 0x583E00
void CRadar::SetBlipFade(int blipIndex, unsigned char fade)
{
	((void(__cdecl *)(int, unsigned char))0x583E00)(blipIndex, fade);
}

// Converted from cdecl void CRadar::SetCoordBlipAppearance(int blipIndex,uchar appearance) 0x583E50
void CRadar::SetCoordBlipAppearance(int blipIndex, unsigned char appearance)
{
	((void(__cdecl *)(int, unsigned char))0x583E50)(blipIndex, appearance);
}

// Converted from cdecl void CRadar::SetBlipFriendly(int blipIndex,uchar friendly) 0x583EB0
void CRadar::SetBlipFriendly(int blipIndex, unsigned char friendly)
{
	((void(__cdecl *)(int, unsigned char))0x583EB0)(blipIndex, friendly);
}

// Converted from cdecl void CRadar::SetBlipEntryExit(int blipIndex,CEntryExit *enex) 0x583F00
void CRadar::SetBlipEntryExit(int blipIndex, CEntryExit* enex)
{
	((void(__cdecl *)(int, CEntryExit*))0x583F00)(blipIndex, enex);
}

// Converted from cdecl void CRadar::ShowRadarTrace(float x,float y,uint size,uchar red,uchar green,uchar blue,uchar alpha) 0x583F40
void CRadar::ShowRadarTrace(float x, float y, unsigned int size, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	((void(__cdecl *)(float, float, unsigned int, unsigned char, unsigned char, unsigned char, unsigned char))0x583F40)(x, y, size, red, green, blue, alpha);
}

// Converted from cdecl void CRadar::ShowRadarTraceWithHeight(float x,float y,uint size,uchar red,uchar green,uchar blue,uchar alpha,uchar type) 0x584070
void CRadar::ShowRadarTraceWithHeight(float x, float y, unsigned int size, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, unsigned char type)
{
	((void(__cdecl *)(float, float, unsigned int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char))0x584070)(x, y, size, red, green, blue, alpha, type);
}

// Converted from cdecl void CRadar::ShowRadarMarker(CVector posn,uint color,float radius) 0x584480
void CRadar::ShowRadarMarker(CVector posn, unsigned int color, float radius)
{
	((void(__cdecl *)(CVector, unsigned int, float))0x584480)(posn, color, radius);
}

// Converted from cdecl uint CRadar::GetRadarTraceColour(uint color,uchar bright, uchar friendly) 0x584770
unsigned int CRadar::GetRadarTraceColour(unsigned int color, unsigned char bright, unsigned char friendly)
{
	return ((unsigned int(__cdecl *)(unsigned int, unsigned char, unsigned char))0x584770)(color, bright, friendly);
}

// Converted from cdecl void CRadar::DrawRotatingRadarSprite(CSprite2d *sprite,float x,float y,float angle,uint width, uint height, CRGBA const&color) 0x584850
void CRadar::DrawRotatingRadarSprite(CSprite2d* sprite, float x, float y, float angle, unsigned int width, unsigned int height, CRGBA color)
{
	((void(__cdecl *)(CSprite2d*, float, float, float, unsigned int, unsigned int, CRGBA))0x584850)(sprite, x, y, angle, width, height, color);
}

// Converted from cdecl void CRadar::DrawYouAreHereSprite(float x,float y) 0x584960
void CRadar::DrawYouAreHereSprite(float x, float y)
{
	((void(__cdecl *)(float, float))0x584960)(x, y);
}

// Converted from cdecl void CRadar::SetupRadarRect(int x,int y) 0x584A80
void CRadar::SetupRadarRect(int x, int y)
{
	((void(__cdecl *)(int, int))0x584A80)(x, y);
}

// Converted from cdecl bool ClipRadarTileCoords(int &x,int &y) 0x584B00
bool ClipRadarTileCoords(int& x, int& y)
{
	return ((bool(__cdecl *)(int&, int&))0x584B00)(x, y);
}

// Converted from cdecl void CRadar::RequestMapSection(int x,int y) 0x584B50
void CRadar::RequestMapSection(int x, int y)
{
	((void(__cdecl *)(int, int))0x584B50)(x, y);
}

// Converted from cdecl void CRadar::RemoveMapSection(int x,int y) 0x584BB0
void CRadar::RemoveMapSection(int x, int y)
{
	((void(__cdecl *)(int, int))0x584BB0)(x, y);
}

// Converted from cdecl void CRadar::RemoveRadarSections(void) 0x584BF0
void CRadar::RemoveRadarSections()
{
	((void(__cdecl *)())0x584BF0)();
}

// Converted from cdecl void CRadar::StreamRadarSections(int x,int y) 0x584C50
void CRadar::StreamRadarSections(int x, int y)
{
	((void(__cdecl *)(int, int))0x584C50)(x, y);
}

// Converted from cdecl bool IsPointInsideRadar(CVector2D const&point) 0x584D40
bool IsPointInsideRadar(CVector2D const& point)
{
	return ((bool(__cdecl *)(CVector2D const&))0x584D40)(point);
}

// Converted from cdecl void GetTextureCorners(int x,int y,CVector2D *corners) 0x584D90
void GetTextureCorners(int x, int y, CVector2D* corners)
{
	((void(__cdecl *)(int, int, CVector2D*))0x584D90)(x, y, corners);
}

// Converted from cdecl int LineRadarBoxCollision(CVector2D &result,CVector2D const&lineStart,CVector2D const&lineEnd) 0x584E00
int LineRadarBoxCollision(CVector2D& result, CVector2D const& lineStart, CVector2D const& lineEnd)
{
	return ((int(__cdecl *)(CVector2D&, CVector2D const&, CVector2D const&))0x584E00)(result, lineStart, lineEnd);
}

// Converted from cdecl int CRadar::ClipRadarPoly(CVector2D *out,CVector2D const*in) 0x585040
int CRadar::ClipRadarPoly(CVector2D* out, CVector2D const* in)
{
	return ((int(__cdecl *)(CVector2D*, CVector2D const*))0x585040)(out, in);
}

// Converted from cdecl void CRadar::DrawAreaOnRadar(CRect const&rect,CRGBA const&color,bool inMenu) 0x5853D0
void CRadar::DrawAreaOnRadar(CRect const& rect, CRGBA const& color, bool inMenu)
{
	((void(__cdecl *)(CRect const&, CRGBA const&, bool))0x5853D0)(rect, color, inMenu);
}

// Converted from cdecl void CRadar::DrawRadarMask(void) 0x585700
void CRadar::DrawRadarMask()
{
	//((void(__cdecl *)())0x585700)();
	float Limit_x = 1 ;
	float Limit_y = abs((CRadar::Radar_Height / CRadar::Radar_Width)) ;
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTURERASTER,(void*)0);
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATESRCBLEND, (void*)5);
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)6);
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)0);
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)2);
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATESHADEMODE, (void*)1);
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE,(void*)0);
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)1);
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)1);
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, (void*)8);
	/////////////////////////////
	//   HOW the points for the vertices are created:
	//     A[0]--------B[1]
	//     |           |
	//     |           |
	//     D[3]--------C[2]
	CVector2D CUT_INPUT[4];
	CVector2D CUT_OUTPUT[4];
	for (int j = 0; j < 4; j++)
	{
		switch (j)
		{
		case 0: //top cut
			CUT_INPUT[0].x = -1.0f;
			CUT_INPUT[0].y = 1.0f;
			CUT_INPUT[1].x = 1.0f;
			CUT_INPUT[1].y = 1.0f;
			CUT_INPUT[2].x = 1.0f;
			CUT_INPUT[2].y = Limit_y;
			CUT_INPUT[3].x = -1.0f;
			CUT_INPUT[3].y = Limit_y;
			break;
		case 1: //bottom cut
			CUT_INPUT[0].x = -1.0f;
			CUT_INPUT[0].y = -Limit_y;
			CUT_INPUT[1].x = 1.0f;
			CUT_INPUT[1].y = -Limit_y;
			CUT_INPUT[2].x = 1.0f;
			CUT_INPUT[2].y = -1.0f;
			CUT_INPUT[3].x = -1.0f;
			CUT_INPUT[3].y = -1.0f;
			break;
		case 2: //left cut
			CUT_INPUT[0].x = -1.0f;
			CUT_INPUT[0].y = 1.0f;
			CUT_INPUT[1].x = -Limit_x;
			CUT_INPUT[1].y = 1.0f;
			CUT_INPUT[2].x = -Limit_x;
			CUT_INPUT[2].y = -1.0f;
			CUT_INPUT[3].x = -1.0f;
			CUT_INPUT[3].y = -1.0f;
			break;
		case 3: //right cut
			CUT_INPUT[0].x = Limit_x;
			CUT_INPUT[0].y = 1.0f;
			CUT_INPUT[1].x = 1.0f;
			CUT_INPUT[1].y = 1.0f;
			CUT_INPUT[2].x = 1.0f;
			CUT_INPUT[2].y = -1.0f;
			CUT_INPUT[3].x = Limit_x;
			CUT_INPUT[3].y = -1.0f;
			break;
		default:
			break;
		}

	/*	for (int i = 0; i < 4; i++)
		{
			CRadar::TransformRadarPointToScreenSpace(CUT_OUTPUT[i], CUT_INPUT[i]);
		}
		CSprite2d::SetMaskVertices(4, CUT_OUTPUT, CSprite2d::NearScreenZ + 0.0000001);
		RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, CSprite2d::maVertices, 4);*/
	}
	 RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, (void*)5);
	return;
}

// Converted from cdecl void CRadar::StreamRadarSections(CVector const&worldPosn) 0x5858D0
void CRadar::StreamRadarSections(CVector const& worldPosn)
{
	((void(__cdecl *)(CVector const&))0x5858D0)(worldPosn);
}

// Converted from cdecl void CRadar::Shutdown(void) 0x585940
void CRadar::Shutdown()
{
	((void(__cdecl *)())0x585940)();
}

// Converted from cdecl void CRadar::InitFrontEndMap(void) 0x585960
void CRadar::InitFrontEndMap()
{
	((void(__cdecl *)())0x585960)();
}

// Converted from cdecl void CRadar::AddBlipToLegendList(uchar,int blipArrId) 0x5859F0
void CRadar::AddBlipToLegendList(unsigned char arg0, int blipArrId)
{
	((void(__cdecl *)(unsigned char, int))0x5859F0)(arg0, blipArrId);
}

// Converted from cdecl void CRadar::SetMapCentreToPlayerCoords(void) 0x585B20
void CRadar::SetMapCentreToPlayerCoords()
{
	((void(__cdecl *)())0x585B20)();
}

void CRadar::SetMapCentreToCoords(float x, float y)
{
	FrontEndMenuManager.drawRadarOrMap = 1;
	CRadar::InitFrontEndMap();
	CVector2D Coords;
	Coords.x = x;
	Coords.y = y;
	CVector2D Coordsout;
	TransformRealWorldPointToRadarSpace(Coordsout, Coords);
	LimitRadarPoint(Coordsout);
	FrontEndMenuManager.drawRadarOrMap = 0;
	FrontEndMenuManager.m_fMapBaseX = 320 - FrontEndMenuManager.m_fMapZoom + Coordsout.x;
	FrontEndMenuManager.m_fMapBaseY =  FrontEndMenuManager.m_fMapZoom * Coordsout.y + 224.0f;
	FrontEndMenuManager.m_vMousePos.x = Coords.x;
	FrontEndMenuManager.m_vMousePos.y = Coords.y;
	FrontEndMenuManager.drawRadarOrMap = 0;
}

// Converted from cdecl void CRadar::Draw3dMarkers(void) 0x585BF0
void CRadar::Draw3dMarkers()
{
	((void(__cdecl *)())0x585BF0)();
}

// Converted from cdecl void CRadar::SetRadarMarkerState(int,uchar) 0x585FE0
void CRadar::SetRadarMarkerState(int arg0, unsigned char arg1)
{
	((void(__cdecl *)(int, unsigned char))0x585FE0)(arg0, arg1);
}

// Converted from cdecl void CRadar::DrawRadarSprite(ushort spriteId,float x,float y,uchar alpha) 0x585FF0
void CRadar::DrawRadarSprite(unsigned short spriteId, float x, float y, unsigned char alpha)
{
	((void(__cdecl *)(unsigned short, float, float, unsigned char))0x585FF0)(spriteId, x, y, alpha);
}

// Converted from cdecl void CRadar::DrawRadarSection(int x,int y) 0x586110
void CRadar::DrawRadarSection(int x, int y)
{
	((void(__cdecl *)(int, int))0x586110)(x, y);
}

// Converted from cdecl void CRadar::DrawRadarSectionMap(int x,int y,CRect rect) 0x586520
void CRadar::DrawRadarSectionMap(int x, int y, CRect rect)
{
	((void(__cdecl *)(int, int, CRect))0x586520)(x, y, rect);
}

// Converted from cdecl void CRadar::DrawRadarGangOverlay(bool inMenu) 0x586650
void CRadar::DrawRadarGangOverlay(bool inMenu)
{
	((void(__cdecl *)(bool))0x586650)(inMenu);
}

// Converted from cdecl void CRadar::DrawRadarMap(void) 0x586880
void CRadar::DrawRadarMap()
{
	((void(__cdecl *)())0x586880)();

}

// Converted from cdecl void CRadar::DrawMap(void) 0x586B00
void CRadar::DrawMap()
{
	((void(__cdecl *)())0x586B00)();
}

// Converted from cdecl void CRadar::DrawCoordBlip(int blipArrId,uchar isSprite) 0x586D60
void CRadar::DrawCoordBlip(int blipArrId, unsigned char isSprite)
{
	((void(__cdecl *)(int, unsigned char))0x586D60)(blipArrId, isSprite);
}

// Converted from cdecl void CRadar::DrawEntityBlip(int blipArrId,uchar) 0x587000
void CRadar::DrawEntityBlip(int blipArrId, unsigned char arg1)
{
	((void(__cdecl *)(int, unsigned char))0x587000)(blipArrId, arg1);
}

// Converted from cdecl void CRadar::ClearActualBlip(int blipArrId) 0x587C10
void CRadar::ClearActualBlip(int blipArrId)
{
	((void(__cdecl *)(int))0x587C10)(blipArrId);
}

// Converted from cdecl void CRadar::ClearBlipForEntity(eBlipType blipType,int entityHandle) 0x587C60
void CRadar::ClearBlipForEntity(eBlipType blipType, int entityHandle)
{
	((void(__cdecl *)(eBlipType, int))0x587C60)(blipType, entityHandle);
}

// Converted from cdecl void CRadar::ClearBlip(int blipIndex) 0x587CE0
void CRadar::ClearBlip(int blipIndex)
{
	((void(__cdecl *)(int))0x587CE0)(blipIndex);
}

// Converted from cdecl void CRadar::SetupAirstripBlips(void) 0x587D20
void CRadar::SetupAirstripBlips()
{
	((void(__cdecl *)())0x587D20)();
}

// Converted from cdecl void CRadar::Initialise(void) 0x587FB0
void CRadar::Initialise()
{
	((void(__cdecl *)())0x587FB0)();
}

// Converted from cdecl void CRadar::DrawBlips(void) 0x588050
void CRadar::DrawBlips()
{
	((void(__cdecl *)())0x588050)();
}

void CRadar::Load()
{
	((void(__cdecl *)())0x5D53C0)();
}

void CRadar::Save()
{
	((void(__cdecl *)())0x5D5860)();
}