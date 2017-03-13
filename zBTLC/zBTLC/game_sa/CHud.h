#pragma once

#include "plbase/PluginBase_SA.h"
#include "CPed.h"

class CHud
{
public:
	// static char m_BigMessage[7][128];
	static char (*m_BigMessage)[128];
	static Bool &bScriptForceDisplayWithCounters;
    static void SetHelpMessage(char const *text, bool quickMessage, bool permanent, bool addToBrief);



	static int Enableclock;

	static float x_fac(float x);
	static float y_fac(float y);
	static void DrawPlayerInfo();
	static void DrawPlayerhealthandarmor(CPed *player);
};