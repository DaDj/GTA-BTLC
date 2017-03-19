#include "CTheScripts.h"

// VARIABLES
char* CTheScripts::ScriptSpace = (char*)VAR_CTheScripts__ScriptSpace;

Bool &CTheScripts::DisplayHud = *(Bool *)0xA444A0;
 Bool &CTheScripts::PlayerisOffMap = *(Bool *)0xA444A4;
tScriptParam *CTheScripts::ScriptParams = (tScriptParam *)0xA43C78;

CRunningScript *&CTheScripts::pIdleScripts = *(CRunningScript **)0xA8B428;
CRunningScript *&CTheScripts::pActiveScripts = *(CRunningScript **)0xA8B42C;