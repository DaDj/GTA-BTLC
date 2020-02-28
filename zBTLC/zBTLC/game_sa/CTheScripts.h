#pragma once
#include "plbase/PluginBase_SA.h"
#include "CRunningScript.h"

#define VAR_CTheScripts__ScriptSpace 0xA49960

union tScriptParam
{
	int iParam;
	float fParam;
};

class CTheScripts
{
public:
	// Script space, where main.scm MAIN section is loaded.
	// Size: 200000 bytes
	static char* ScriptSpace;
	static bool &DisplayHud;
	static bool &PlayerisOffMap;
	static tScriptParam *ScriptParams;
	static int &bDrawCrossHair;
    static CRunningScript *&pIdleScripts;
    static CRunningScript *&pActiveScripts;
};