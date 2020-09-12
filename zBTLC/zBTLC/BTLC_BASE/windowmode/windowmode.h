#pragma once
#include <Windows.h>
#include "../../game_sa/CVideomodemanager.h"
#include "../../game_sa/CMenuManager.h"
#include "../../game_sa/RenderWare.h"
#include <iostream>




 
int SetupWindowStyle();

char** __cdecl FIND_VIDEOMODES();

int  psSelectDevice();


HWND INITINSTANCE(HINSTANCE hinstance);