#pragma once
#include <Windows.h>
#include "../../game_sa/CVideomodemanager.h"
#include "../../game_sa/CMenuManager.h"
#include "../../game_sa/RenderWare.h"
#include <iostream>

void changeresu();

char** __cdecl FIND_VIDEOMODES();

int __cdecl psSelectDevice();

HWND INITINSTANCE(HINSTANCE hinstance);