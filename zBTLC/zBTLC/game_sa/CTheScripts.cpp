#include "CTheScripts.h"

// VARIABLES
char* CTheScripts::ScriptSpace = (char*)VAR_CTheScripts__ScriptSpace;

bool &CTheScripts::DisplayHud = *(bool *)0xA444A0;
 bool &CTheScripts::PlayerisOffMap = *(bool *)0xA444A4;
tScriptParam *CTheScripts::ScriptParams = (tScriptParam *)0xA43C78;
 int &CTheScripts::bDrawCrossHair = *(int *)0xA44490;
CRunningScript *&CTheScripts::pIdleScripts = *(CRunningScript **)0xA8B428;
CRunningScript *&CTheScripts::pActiveScripts = *(CRunningScript **)0xA8B42C;