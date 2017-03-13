#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <utility>
#include <ctime>

//SA things
#include "Patch\MemoryMgr.h"
#include "Patch\calling.hpp"
#include "Patch\hooking.hpp"
#include "Patch\injector.hpp"
#include "Events_SA\EventList.h"
#include "Events_SA\Events_SA.h"
#pragma warning(disable:4244) 
#pragma warning(disable:4309) 

//RENDERWARE
//#include "game_sa\rw\rphanim.h"
//#include "game_sa\rw\rpmatfx.h"
//#include "game_sa\rw\rpskin.h"
//#include "game_sa\rw\rpuvanim.h"
//#include "game_sa\rw\rpworld.h"
//#include "game_sa\rw\rtanim.h"
//#include "game_sa\rw\rtdict.h"
//#include "game_sa\rw\rtquat.h"
//#include "game_sa\rw\rwcore.h"
//#include "game_sa\rw\rwplcore.h"
//#include "game_sa\rw\skeleton.h"