#include "CCoronas.h"

float& CCoronas::SunScreenX = *(float *)0xC3E028;
float& CCoronas::SunScreenY = *(float *)0xC3E02C;
unsigned char& CCoronas::SunBlockedByClouds = *(unsigned char *)0xC3E030;
bool& CCoronas::bChangeBrightnessImmediately = *(bool *)0xC3E034;
unsigned int& CCoronas::NumRegisteredCoronas = *(unsigned int *)0xC3E038;
float& CCoronas::LightsMult = *(float *)0x8D4B5C;
unsigned int& CCoronas::MoonSize = *(unsigned int *)0x8D4B60;

RwTexture* (&gpCoronaTexture)[CORONA_TEXTURES_COUNT] = *(RwTexture*(*)[CORONA_TEXTURES_COUNT])0xC3E000;
CRegisteredCorona(&CCoronas::aCoronas)[MAX_NUM_CORONAS] = *(CRegisteredCorona(*)[MAX_NUM_CORONAS])0xC3E058;

uint16(&CCoronas::ms_aEntityLightsOffsets)[8] = *(uint16(*)[8])0x8D5028;
char(&coronaTexturesAlphaMasks)[260] = *(char(*)[260])0x8D4A58;

void CCoronas::Init()
{
	((void (__cdecl *)())0x6FAA70)();
}

void CCoronas::Shutdown()
{
	((void (__cdecl *)())0x6FAB00)();
}

void CCoronas::Update()
{
	((void (__cdecl *)())0x6FADF0)();
}

void CCoronas::Render()
{
	((void (__cdecl *)())0x6FAEC0)();
}

void CCoronas::RenderReflections()
{
	((void (__cdecl *)())0x6FB630)();
}

void CCoronas::RenderSunReflection()
{
	((void (__cdecl *)())0x6FBAA0)();
}

void CCoronas::RegisterCorona(unsigned int id, CEntity *attachTo, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const &posn, float radius, float farClip, RwTexture *texture, unsigned char flare, bool enableReflection, bool checkObstacles, int _param_not_used, float angle, bool longDistance, float nearClip, unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay)
{
	((void (__cdecl *)(unsigned int, CEntity *, unsigned char, unsigned char, unsigned char, unsigned char, CVector const &, float, float, RwTexture *, unsigned char, bool, bool, int, float, bool, float, unsigned char, float, bool, bool))0x6FC180)(id, attachTo, red, green, blue, alpha, posn, radius, farClip, texture, flare, enableReflection, checkObstacles, _param_not_used, angle, longDistance, nearClip, fadeState, fadeSpeed, onlyFromBelow, reflectionDelay);
}

void CCoronas::RegisterCorona(unsigned int id, CEntity *attachTo, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const &posn, float radius, float farClip, eCoronaType coronaType, unsigned char flare, bool enableReflection, bool checkObstacles, int _param_not_used, float angle, bool longDistance, float nearClip, unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay)
{
	((void (__cdecl *)(unsigned int, CEntity *, unsigned char, unsigned char, unsigned char, unsigned char, CVector const &, float, float, unsigned char, unsigned char, bool, bool, int, float, bool, float, unsigned char, float, bool, bool))0x6FC580)(id, attachTo, red, green, blue, alpha, posn, radius, farClip, coronaType, flare, enableReflection, checkObstacles, _param_not_used, angle, longDistance, nearClip, fadeState, fadeSpeed, onlyFromBelow, reflectionDelay);
}

void CCoronas::UpdateCoronaCoors(unsigned int id, CVector  const& posn, float farClip, float angle)
{
	((void (__cdecl *)(unsigned int, CVector  const&, float, float))0x6FC4D0)(id, posn, farClip, angle);
}

void CCoronas::DoSunAndMoon()
{
	((void (__cdecl *)())0x6FC5A0)();
}