#pragma once
#include "debugmenu_public.h"

typedef uint8_t uint8, uchar;
typedef uint16_t uint16, ushort;
typedef uint32_t uint32, uint;
typedef uint64_t uint64;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

namespace debug {

	void init();
	void debug_console();
	void draw_current_Modelname();
	void draw_FPS();
	void draw_graphics_info();

	void DebugMenuInit(void);

	void DebugMenuSetup();


}

