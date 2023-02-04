#pragma once

#include "plbase/PluginBase_SA.h"
#include "CRegisteredCorona.h"

#define MAX_NUM_CORONAS 64

class CCoronas
{
public:
	// sun 2d position
	static float& SunScreenX;
	static float& SunScreenY;
	// are there any obstacles between sun and camera
	static unsigned char& SunBlockedByClouds;
	// change coronas brightness immediately
	static bool& bChangeBrightnessImmediately;
	// num of registered coronas in frame
	static unsigned int& NumRegisteredCoronas;
	// coronas intensity multiplier
	static float& LightsMult;
	// this is used to control moon size when you shooting it with sniper
	static unsigned int& MoonSize;
	// Coronas array. count: MAX_NUM_CORONAS (64)
	static CRegisteredCorona(&aCoronas)[MAX_NUM_CORONAS];
	static uint16(&ms_aEntityLightsOffsets)[8];


	// Initialises coronas
	static void Init();
	// Terminates coronas
	static void Shutdown();
	// Updates coronas
	static void Update();
	// Renders coronas
	static void Render();
	// Renders coronas reflections on a wet ground
	static void RenderReflections();
	// Renders sun reflection on a water
	static void RenderSunReflection();
	// Creates corona by texture
	static void RegisterCorona(unsigned int id, CEntity *attachTo, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const &posn, float radius, float farClip, RwTexture *texture, unsigned char flare, bool enableReflection, bool checkObstacles, int _param_not_used, float angle, bool longDistance, float nearClip, unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay);
	// Creates corona by type
	static void RegisterCorona(unsigned int id, CEntity *attachTo, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector const &posn, float radius, float farClip, eCoronaType coronaType, unsigned char flare, bool enableReflection, bool checkObstacles, int _param_not_used, float angle, bool longDistance, float nearClip, unsigned char fadeState, float fadeSpeed, bool onlyFromBelow, bool reflectionDelay);
	static void UpdateCoronaCoors(unsigned int id, CVector  const& posn, float farClip, float angle);
	// Draw sun (Moon went to CClouds since SA)
	static void DoSunAndMoon();
};	
extern uint32 MAX_CORONAS;
constexpr int32 CORONA_TEXTURES_COUNT = 10;
extern RwTexture* (&gpCoronaTexture)[CORONA_TEXTURES_COUNT];